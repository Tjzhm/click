#ifndef AVERAGECOUNTER_HH
#define AVERAGECOUNTER_HH
#include <click/element.hh>
#include <click/ewma.hh>
#include <click/timer.hh>

/*
 * =c
 * AverageCounter()
 * =s
 * measures historical packet count and rate
 * V<measurement>
 * =d
 *
 * Passes packets unchanged from its input to its output, maintaining
 * statistics information about packet count and packet rate using a strict
 * average.
 *
 * The rate covers only the time between the first and most recent
 * packets.
 *
 * =h count read-only
 * Returns the number of packets that have passed through.
 *
 * =h rate read-only
 * Returns packet arrival rate.
 *
 * =h reset write-only
 * Resets the count and rate to zero.
 */

class AverageCounter : public Element { protected:
  
  int _count;
  unsigned long _first;
  unsigned long _last;
  
 public:

  AverageCounter();
  ~AverageCounter();
  
  const char *class_name() const		{ return "AverageCounter"; }
  const char *processing() const		{ return AGNOSTIC; }

  int count() const				{ return _count; }
  unsigned long first() const			{ return _first; }
  unsigned long last() const			{ return _last; }
  void reset();
  
  AverageCounter *clone() const			{ return new AverageCounter; }
  int initialize(ErrorHandler *);
  void add_handlers();
  
  Packet *simple_action(Packet *);
  
};

#endif
