/******************************************************************************
 *
 * $Id: osisplain.h,v 1.11 2004/04/09 12:31:18 joachim Exp $
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

#ifndef OSISPLAIN_H
#define OSISPLAIN_H

#include <swbasicfilter.h>
#include <utilxml.h>

SWORD_NAMESPACE_START

/** this filter converts OSIS text to plain text
 */
class SWDLLEXPORT OSISPlain : public SWBasicFilter {
public:
protected:
	class MyUserData : public BasicFilterUserData {
	public:
		SWBuf w;
		XMLTag tag;
		MyUserData(const SWModule *module, const SWKey *key) : BasicFilterUserData(module, key) {}
	};
	virtual BasicFilterUserData *createUserData(const SWModule *module, const SWKey *key) {
		return new MyUserData(module, key);
	}
	virtual bool handleToken(SWBuf &buf, const char *token, BasicFilterUserData *userData);
public:
	OSISPlain();
};

SWORD_NAMESPACE_END
#endif
