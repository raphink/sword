/*
 *
 * $Id: gbfredletterwords.h,v 1.1 2003/01/14 19:30:18 joachim Exp $
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

#ifndef GBFSREDLETTERWORDS_H
#define GBFREDLETTERWORDS_H

#include <swfilter.h>

#include <defs.h>

SWORD_NAMESPACE_START

  /** This Filter shows/hides strong's numbers in a GBF text
  */
class SWDLLEXPORT GBFRedLetterWords : public SWFilter
{
  bool option;
  static const char on[];
  static const char off[];
  static const char optName[];
  static const char optTip[];
  OptionsList options;
public:
    GBFRedLetterWords ();
    virtual ~ GBFRedLetterWords ();
  virtual char ProcessText (char *text, int maxlen, const SWKey * key, const SWModule * = 0);
  virtual const char *getOptionName ()
  {
    return optName;
  }
  virtual const char *getOptionTip ()
  {
    return optTip;
  }
  virtual void setOptionValue (const char *ival);
  virtual const char *getOptionValue ();
  virtual OptionsList getOptionValues ()
  {
    return options;
  }
};

SWORD_NAMESPACE_END
#endif
