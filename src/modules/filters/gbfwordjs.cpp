/******************************************************************************
 *
 * gbfstrongs -	SWFilter descendant to hide or show strongs number
 *			in a GBF module.
 */


#include <stdlib.h>
#include <gbfwordjs.h>
#include <swmodule.h>
#include <ctype.h>
#include <utilxml.h>
#include <utilstr.h>
#include <versekey.h>

SWORD_NAMESPACE_START

const char oName[] = "Word Javascript";
const char oTip[] = "Toggles Word Javascript data";

const SWBuf choices[3] = {"Off", "On", ""};
const StringList oValues(&choices[0], &choices[2]);


GBFWordJS::GBFWordJS() : SWOptionFilter(oName, oTip, &oValues) {
	setOptionValue("Off");

     defaultGreekLex   = 0;
     defaultHebLex     = 0;
     defaultGreekParse = 0;
     defaultHebParse   = 0;
     mgr               = 0;
}


GBFWordJS::~GBFWordJS() {
}


char GBFWordJS::processText(SWBuf &text, const SWKey *key, const SWModule *module) {
	if (option) {
		char token[2112]; // cheese.  Fix.
		int tokpos = 0;
		bool intoken = false;
		bool lastspace = false;
		int word = 1;
		char val[128];
		char *valto;
		char *ch;
		char wordstr[5];
		unsigned int textStart = 0, lastAppendLen = 0, textEnd = 0;
		char gh = 0;
		SWBuf tmp;
		bool newText = false;
		bool needWordOut = false;
		AttributeValue *wordAttrs = 0;
		SWBuf modName = (module)?module->Name():"";
		SWBuf wordSrcPrefix = modName;
		
		const SWBuf orig = text;
		const char * from = orig.c_str();
		VerseKey *vkey = 0;
		if (key) {
			vkey = SWDYNAMIC_CAST(VerseKey, key);
		}

		for (text = ""; *from; from++) {
			if (*from == '<') {
				intoken = true;
				tokpos = 0;
				token[0] = 0;
				token[1] = 0;
				token[2] = 0;
				textEnd = text.length();
				continue;
			}
			if (*from == '>') {	// process tokens
				intoken = false;
				if (*token == 'W' && (token[1] == 'G' || token[1] == 'H')) {	// Strongs
					strcpy(val,token+1);
					if (atoi((!isdigit(*val))?val+1:val) < 5627) {
						// normal strongs number
						sprintf(wordstr, "%03d", word++);
						needWordOut = (word > 2);
						wordAttrs = &(module->getEntryAttributes()["Word"][wordstr]);
						(*wordAttrs)["Lemma"] = val;
	//printf("Adding: [\"Word\"][%s][\"Strongs\"] = %s\n", wordstr, val);
						tmp = "";
						tmp.append(text.c_str()+textStart, (int)(textEnd - textStart));
						(*wordAttrs)["Text"] = tmp;
						text.append("</span>");
						SWBuf ts;
						ts.appendFormatted("%d", textStart);
						(*wordAttrs)["TextStart"] = ts;
	//printf("Adding: [\"Word\"][%s][\"Text\"] = %s\n", wordstr, tmp.c_str());
						newText = true;
					}
					else {
						// verb morph
						(*wordAttrs)["Morph"] = val;
	//printf("Adding: [\"Word\"][%s][\"Morph\"] = %s\n", wordstr, val);
					}

				}
				if (*token == 'W' && token[1] == 'T') {	// Morph
					if (token[2] == 'G' || token[2] == 'H') {
						strcpy(val, token+2);
					}
					else strcpy(val, token+1);
					(*wordAttrs)["Morph"] = val;
					(*wordAttrs)["MorphClass"] = "StrongsMorph";
					newText = true;
				}
				// if not a strongs token, keep token in text
				text += '<';
				text += token;
				text += '>';
				if (needWordOut) {
					char wstr[10];
					sprintf(wstr, "%03d", word-2);
					AttributeValue *wAttrs = &(module->getEntryAttributes()["Word"][wstr]);
					needWordOut = false;
					SWBuf strong = (*wAttrs)["Lemma"];
					SWBuf morph = (*wAttrs)["Morph"];
					SWBuf morphClass = (*wAttrs)["MorphClass"];
					SWBuf wordText = (*wAttrs)["Text"];
					SWBuf textSt = (*wAttrs)["TextStart"];
					if (strong.size()) {
						char gh = 0;
						gh = isdigit(strong[0]) ? 0:strong[0];
						if (!gh) {
							if (vkey) {
								gh = vkey->Testament() ? 'H' : 'G';
							}
						}
						else strong << 1;

						SWModule *sLex = 0;
						SWModule *sMorph = 0;
						if (gh == 'G') {
							sLex = defaultGreekLex;
							sMorph = defaultGreekParse;
						}
						if (gh == 'H') {
							sLex = defaultHebLex;
							sMorph = defaultHebParse;
						}
						SWBuf lexName = "";
						if (sLex) {
							// we can pass the real lex name in, but we have some
							// aliases in the javascript to optimize bandwidth
							lexName = sLex->Name();
							if (lexName == "StrongsGreek")
								lexName = "G";
							if (lexName == "StrongsHebrew")
								lexName = "H";
						}
						SWBuf wordID;
						if (vkey) {
							// optimize for bandwidth and use only the verse as the unique entry id
							wordID.appendFormatted("%d", vkey->Verse());
						}
						else {
							wordID = key->getText();
						}
						for (int i = 0; i < wordID.size(); i++) {
							if ((!isdigit(wordID[i])) && (!isalpha(wordID[i]))) {
								wordID[i] = '_';
							}
						}
						wordID.appendFormatted("_%s%d", wordSrcPrefix.c_str(), atoi(wstr));
						if (textSt.size()) {
							int textStr = atoi(textSt.c_str());
							textStr += lastAppendLen;
							SWBuf spanStart = "";



/*
							if (sMorph) {
								SWBuf popMorph = "<a onclick=\"";
								popMorph.appendFormatted("p(\'%s\',\'%s\','%s','');\" >%s</a>", sMorph->Name(), morph.c_str(), wordID.c_str(), morph.c_str());
								morph = popMorph;
							}
*/

							// 'p' = 'fillpop' to save bandwidth
							const char *m = strchr(morph.c_str(), ':');
							if (m) m++;
							else m = morph.c_str();
							spanStart.appendFormatted("<span class=\"clk\" onclick=\"p(\'%s\',\'%s\','%s','%s');\" >", lexName.c_str(), strong.c_str(), wordID.c_str(), m);
							text.insert(textStr, spanStart);
							lastAppendLen = spanStart.length();
						}
					}

				}
				if (newText) {
					textStart = text.length(); newText = false;
				}
				continue;
			}
			if (intoken) {
				if (tokpos < 2045)
					token[tokpos++] = *from;
					token[tokpos+2] = 0;
			}
			else	{
				text += *from;
				lastspace = (*from == ' ');
			}
		}

		char wstr[10];
		sprintf(wstr, "%03d", word-1);
		AttributeValue *wAttrs = &(module->getEntryAttributes()["Word"][wstr]);
		needWordOut = false;
		SWBuf strong = (*wAttrs)["Lemma"];
		SWBuf morph = (*wAttrs)["Morph"];
		SWBuf morphClass = (*wAttrs)["MorphClass"];
		SWBuf wordText = (*wAttrs)["Text"];
		SWBuf textSt = (*wAttrs)["TextStart"];
		if (strong.size()) {
			char gh = 0;
			gh = isdigit(strong[0]) ? 0:strong[0];
			if (!gh) {
				if (vkey) {
					gh = vkey->Testament() ? 'H' : 'G';
				}
			}
			else strong << 1;

			SWModule *sLex = 0;
			if (gh == 'G') {
				sLex = defaultGreekLex;
			}
			if (gh == 'H') {
				sLex = defaultHebLex;
			}
			SWBuf lexName = "";
			if (sLex) {
				// we can pass the real lex name in, but we have some
				// aliases in the javascript to optimize bandwidth
				lexName = sLex->Name();
				if (lexName == "StrongsGreek")
					lexName = "G";
				if (lexName == "StrongsHebrew")
					lexName = "H";
			}
			SWBuf wordID;
			if (vkey) {
				// optimize for bandwidth and use only the verse as the unique entry id
				wordID.appendFormatted("%d", vkey->Verse());
			}
			else {
				wordID = key->getText();
			}
			for (int i = 0; i < wordID.size(); i++) {
				if ((!isdigit(wordID[i])) && (!isalpha(wordID[i]))) {
					wordID[i] = '_';
				}
			}
			wordID.appendFormatted("_%s%d", wordSrcPrefix.c_str(), atoi(wstr));
			if (textSt.size()) {
				int textStr = atoi(textSt.c_str());
				textStr += lastAppendLen;
				SWBuf spanStart = "";
				// 'p' = 'fillpop' to save bandwidth
				const char *m = strchr(morph.c_str(), ':');
				if (m) m++;
				else m = morph.c_str();
				spanStart.appendFormatted("<span class=\"clk\" onclick=\"p(\'%s\',\'%s\','%s','%s');\" >", lexName.c_str(), strong.c_str(), wordID.c_str(), m);
				text.insert(textStr, spanStart);
			}
		}
	}

	return 0;
}

SWORD_NAMESPACE_END
