/******************************************************************************
 *
 * $Id: thmlgbf.h,v 1.7 2003/07/26 23:10:55 chrislit Exp $
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

#ifndef THMLGBF_H
#define THMLGBF_H

#include <swfilter.h>

SWORD_NAMESPACE_START

/** this filter converts ThML text to GBF text
 */
class SWDLLEXPORT ThMLGBF : public SWFilter {
protected:
	virtual char processText(SWBuf &text, const SWKey *key = 0, const SWModule *module = 0);
public:
	ThMLGBF();
};

SWORD_NAMESPACE_END
#endif
