/******************************************************************************
 *  swfilter.h	- definition of class SWFilter used to filter text between
 *				different formats
 *
 * $Id$
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

#ifndef SWFILTER_H
#define SWFILTER_H

#include <defs.h>
#include <swbuf.h>
#include <list>
#include <swkey.h>

SWORD_NAMESPACE_START

/**
* The type definitoin for option types
*/
typedef std::list < SWBuf > StringList;

class SWModule;

/** Base class for all filters in sword.
* Filters are used to filter/convert text between different formats
* like GBF, HTML, RTF ...
*/
class SWDLLEXPORT  SWFilter {
public:
	virtual ~SWFilter() {}

	/** gets the name of the option of this filter
	 * @return option name
	 */
	virtual const char *getOptionName () { return 0; }

	/** gets a short explanation of the option of this filter;
	 * it could be presented to the user in frontend programs
	 * @return option tip/explanation
	 */
	virtual const char *getOptionTip () { return 0; }

	/** returns a list of the possible option values
	 * 
	 * @return list of option values
	 */
	virtual StringList getOptionValues () {
		StringList options;
		return options;
	}

	/** @return The value of the current option.
	*/
	virtual const char *getOptionValue () { return 0; }

	/** sets the value of the option of this filter,
	 * e.g maybe a strong's filter mioght be set to "on" / "off" -
	 * that would mean to show or not to show the strongs in the text,
	 * see also getOptionValues()
	 * @param ival the new option valus
	 */
	virtual void setOptionValue (const char */*ival*/) { }

	/** This is the main filter function
	 * @param text The text to be filtered/converted
	 * @param key Current key That was used.
	 * @param module Current module.
	 * @return 0
	 */
	virtual char processText(SWBuf &text, const SWKey *key = 0, const SWModule *module = 0) = 0;
};

	SWORD_NAMESPACE_END
#endif
