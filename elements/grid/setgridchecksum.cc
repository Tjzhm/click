/*
 * setgridchecksum.{cc,hh} -- element sets Grid header checksum
 * Douglas S. J. De Couto
 * adapted from setipchecksum.{cc,hh} by Robert Morris
 *
 * Copyright (c) 1999-2000 Massachusetts Institute of Technology.
 *
 * This software is being provided by the copyright holders under the GNU
 * General Public License, either version 2 or, at your discretion, any later
 * version. For more information, see the `COPYRIGHT' file in the source
 * distribution.
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif
#include "setgridchecksum.hh"
#include "glue.hh"
#include "grid.hh"
#include "click_ether.h"

SetGridChecksum::SetGridChecksum()
{
  add_input();
  add_output();
}

SetGridChecksum::~SetGridChecksum()
{
}

SetGridChecksum *
SetGridChecksum::clone() const
{
  return new SetGridChecksum();
}

Packet *
SetGridChecksum::simple_action(Packet *p)
{
  grid_hdr *gh = (grid_hdr *) (p->data() + sizeof(click_ether));
  unsigned plen = p->length();
  unsigned hlen;
  
  if (!gh || plen < sizeof(grid_hdr) + sizeof(click_ether))
    goto bad;

  hlen = gh->hdr_len;
  if (/* hlen < sizeof(grid_hdr) || */ // grid_hdr size keeps changing...
      hlen > plen)
    goto bad;

  gh->cksum = 0;
  gh->cksum = in_cksum((unsigned char *) gh, hlen);
  
  return p;

 bad:
  click_chatter("SetGridChecksum: bad lengths");
  p->kill();
  return(0);
}

EXPORT_ELEMENT(SetGridChecksum)
