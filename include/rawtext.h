/******************************************************************************
 *  rawtext.h   - code for class 'RawText'- a module that reads raw text files:
 *		  ot and nt using indexs ??.bks ??.cps ??.vss
 *
 * $Id: rawtext.h,v 1.12 2001/06/12 06:27:24 scribe Exp $
 *
 * Copyright 1998 CrossWire Bible Society (http://www.crosswire.org)
 *	CrossWire Bible Society
 *	P. O. Box 2528
 *	Tempe, AZ  85280-2528
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation version 2.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 */

#ifndef RAWTEXT_H
#define RAWTEXT_H

#include <rawverse.h>
#include <rawstr.h>
#include <swtext.h>

#include <defs.h>

class SWDLLEXPORT RawText:public SWText, public RawVerse
{
  char *versebuf;
  RawStr *fastSearch[2];

public:
  
    
    RawText (const char *ipath, const char *iname = 0, const char *idesc =	0, SWDisplay * idisp = 0, bool unicode = false);
    virtual ~ RawText ();
  virtual char *getRawEntry ();
  virtual char createSearchFramework ();
  virtual bool hasSearchFramework ()
  {
    return true;
  }
#ifdef __VISUALC__
  virtual SWModule & operator = (SW_POSITION);
#else
  virtual RawText & operator = (SW_POSITION);
#endif
  virtual ListKey & Search (const char *istr, int searchType = 0, int flags =
			    0, SWKey * scope =
			    0, bool * justCheckIfSupported =
			    0, void (*percent) (char, void *) =
			    &SWModule::nullPercent, void *percentUserData =
			    0);

  // write interface ----------------------------
  virtual bool isWritable ()
  {
    return true;
  }
  static char createModule (const char *path)
  {
    return RawVerse::createModule (path);
  }
  virtual SWModule & operator << (const char *inbuf);	// Modify current module entry
  virtual SWModule & operator << (const SWKey * linkKey);	// Link current module entry to other module entry
  virtual void deleteEntry ();	// Delete current module entry
  // end write interface ------------------------
};


#endif
