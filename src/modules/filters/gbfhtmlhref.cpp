/***************************************************************************
                          gbfhtmlhref.cpp  -   GBF to HTML filter with hrefs 
			        for strongs and morph tags
                             -------------------
    begin                    : 2001-09-03
    copyright            : 2001 by CrossWire Bible Society
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <gbfhtmlhref.h>
#include <ctype.h>

SWORD_NAMESPACE_START

GBFHTMLHREF::GBFHTMLHREF() {
	setTokenStart("<");
	setTokenEnd(">");
	
	setTokenCaseSensitive(true);

	addTokenSubstitute("Rf", ")</small></font>");
	addTokenSubstitute("Rx", "</a>");
	addTokenSubstitute("FI", "<i>"); // italics begin
	addTokenSubstitute("Fi", "</i>");
	addTokenSubstitute("FB", "<b>"); // bold begin
	addTokenSubstitute("Fb", "</b>");
	addTokenSubstitute("FR", "<font color=\"#FF0000\">"); // words of Jesus begin
	addTokenSubstitute("Fr", "</font>");
	addTokenSubstitute("FU", "<u>"); // underline begin
	addTokenSubstitute("Fu", "</u>");
	addTokenSubstitute("FO", "<cite>"); //  Old Testament quote begin
	addTokenSubstitute("Fo", "</cite>");
	addTokenSubstitute("FS", "<sup>"); // Superscript begin// Subscript begin
	addTokenSubstitute("Fs", "</sup>");
	addTokenSubstitute("FV", "<sub>"); // Subscript begin
	addTokenSubstitute("Fv", "</sub>");
	addTokenSubstitute("TT", "<big>"); // Book title begin
	addTokenSubstitute("Tt", "</big>");
	addTokenSubstitute("PP", "<cite>"); //  poetry  begin
	addTokenSubstitute("Pp", "</cite>");
	addTokenSubstitute("Fn", "</font>"); //  font  end
	addTokenSubstitute("CL", "<br />"); //  new line
	addTokenSubstitute("CM", "<!P><br />"); //  paragraph <!P> is a non showing comment that can be changed in the front end to <P> if desired
	addTokenSubstitute("CG", ""); //  ???
	addTokenSubstitute("CT", ""); // ???
	addTokenSubstitute("JR", "<div align=\"right\">"); // right align begin
	addTokenSubstitute("JC", "<div align=\"center\">"); // center align begin
	addTokenSubstitute("JL", "</div>"); // align end
	
}


bool GBFHTMLHREF::handleToken(SWBuf &buf, const char *token, UserData *userData) {
	const char *tok;
	char val[128];
	char *valto;
	const char *num;
	MyUserData *u = (MyUserData *)userData;

	if (!substituteToken(buf, token)) {		
		// deal with OSIS note tags.  Just hide till OSISRTF		
		if (!strncmp(token, "note ", 5)) {
			// let's stop text from going to output
			u->suspendTextPassThru = true;
		}
		
		else if (!strncmp(token, "/note", 5)) {
			u->suspendTextPassThru = false;
		}		

		else if (!strncmp(token, "w", 1)) {
			// OSIS Word (temporary until OSISRTF is done)
			valto = val;
			num = strstr(token, "lemma=\"x-Strongs:");
			if (num) {
				for (num+=17; ((*num) && (*num != '\"')); num++)
					*valto++ = *num;
				*valto = 0;
				if (atoi((!isdigit(*val))?val+1:val) < 5627) {
					buf += " <small><em>&lt;<a href=\"type=Strongs value=";
					for (tok = val; *tok; tok++)
							buf += *tok;
					buf += "\">";
					for (tok = (!isdigit(*val))?val+1:val; *tok; tok++)
							buf += *tok;
					buf += "</a>&gt;</em></small> ";
					//cout << buf;
					
				}
				/*	forget these for now
				else {
					// verb morph
					sprintf(wordstr, "%03d", word-1);
					module->getEntryAttributes()["Word"][wordstr]["Morph"] = val;
				}
				*/
			}
			valto = val;
			num = strstr(token, "morph=\"x-Robinson:");
			if (num) {
				for (num+=18; ((*num) && (*num != '\"')); num++)
					*valto++ = *num;
				*valto = 0;
				buf += " <small><em>(<a href=\"type=morph class=Robinson value=";
				for (tok = val; *tok; tok++)
				// normal robinsons tense
						buf += *tok;
				buf += "\">";
				for (tok = val; *tok; tok++)				
					//if(*tok != '\"') 			
						buf += *tok;		
				buf += "</a>)</em></small> ";					
			}
		}
		
		else if (!strncmp(token, "WG", 2) || !strncmp(token, "WH", 2)) { // strong's numbers
			buf += " <small><em>&lt;<a href=\"type=Strongs value=";
			for (tok = token+1; *tok; tok++)
				//if(token[i] != '\"')
					buf += *tok;
			buf += "\">";
			for (tok = token + 2; *tok; tok++)
				//if(token[i] != '\"')
					buf += *tok;
			buf += "</a>&gt;</em></small>";
		}

		else if (!strncmp(token, "WTG", 3) || !strncmp(token, "WTH", 3)) { // strong's numbers tense
			buf += " <small><em>(<a href=\"type=Strongs value=";
			for (tok = token + 2; *tok; tok++)
				if(*tok != '\"')
					buf += *tok;
			buf += "\">";
			for (tok = token + 3; *tok; tok++)
				if(*tok != '\"')
					buf += *tok;
			buf += "</a>)</em></small>";
		}

		else if (!strncmp(token, "WT", 2) && strncmp(token, "WTH", 3) && strncmp(token, "WTG", 3)) { // morph tags
			buf += " <small><em>(<a href=\"type=morph class=none value=";
			for (tok = token + 2; *tok; tok++)
				if(*tok != '\"')
					buf += *tok;
			buf += "\">";
			for (tok = token + 2; *tok; tok++)				
				if(*tok != '\"') 			
					buf += *tok;		
			buf += "</a>)</em></small>";
		}

		else if (!strncmp(token, "RX", 2)) {
			buf += "<a href=\"";
			for (tok = token + 3; *tok; tok++) {
			  if(*tok != '<' && *tok+1 != 'R' && *tok+2 != 'x') {
			    buf += *tok;
			  }
			  else {
			    break;
			  }
			}
			buf += "\">";
		}

		else if (!strncmp(token, "RB", 2)) {
			buf += "<i> ";
			u->hasFootnotePreTag = true;
		}

		else if (!strncmp(token, "RF", 2)) {
			if (u->hasFootnotePreTag) {
				u->hasFootnotePreTag = false;
				buf += "</i> ";
			}
			buf += "<font color=\"#800000\"><small> (";
		}

		else if (!strncmp(token, "FN", 2)) {
			buf += "<font face=\"";
			for (tok = token + 2; *tok; tok++)				
				if(*tok != '\"') 			
					buf += *tok;
			buf += "\">";
		}

		else if (!strncmp(token, "CA", 2)) {	// ASCII value
			buf += (char)atoi(&token[2]);
		}
		
		else {
			return false;
		}
	}
	return true;
}

SWORD_NAMESPACE_END
