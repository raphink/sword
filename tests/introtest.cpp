#include <swmgr.h>
#include <iostream.h>
#include <versekey.h>
#include <rawtext.h>

int main(int argc, char **argv) {
	SWMgr mymgr;

	RawText::createModule(".");
	RawText mod(".");

	VerseKey vk;
	vk.Headings(1);
	vk.AutoNormalize(0);
	vk.Persist(1);
	mod.SetKey(vk);

	vk.Verse(0);
	vk.Chapter(0);
	vk.Book(0);
	vk.Testament(0);

	mod << "Module heading text";

	vk.Verse(0);
	vk.Chapter(0);
	vk.Book(0);
	vk.Testament(1);

	mod << "OT heading text";

	vk.Verse(0);
	vk.Chapter(0);
	vk.Book(1);
	vk.Testament(1);

	mod << "Gen heading text";

	vk.Verse(0);
	vk.Chapter(1);
	vk.Book(1);
	vk.Testament(1);

	mod << "Gen 1 heading text";

	vk.Verse(1);
	vk.Chapter(1);
	vk.Book(1);
	vk.Testament(1);

	mod << "Gen 1:1 text";

	
	vk.Verse(0);
	vk.Chapter(0);
	vk.Book(0);
	vk.Testament(0);

	cout << "Module heading text ?= " << (const char*)mod << endl;

	vk.Verse(0);
	vk.Chapter(0);
	vk.Book(0);
	vk.Testament(1);

	cout << "OT heading text ?= " << (const char*)mod << endl;

	vk.Verse(0);
	vk.Chapter(0);
	vk.Book(1);
	vk.Testament(1);

	cout << "Gen heading text ?= " << (const char*)mod << endl;

	vk.Verse(0);
	vk.Chapter(1);
	vk.Book(1);
	vk.Testament(1);

	cout << "Gen 1 heading text ?= " << (const char*)mod << endl;

	vk.Verse(1);
	vk.Chapter(1);
	vk.Book(1);
	vk.Testament(1);

	cout << "Gen 1:1 text ?= " << (const char*)mod << endl;

	  /* old introtest
	SWModule *mhc = mymgr.Modules["MHC"];

	if (mhc) {
		VerseKey vk;
		vk.Headings(1);
		vk.AutoNormalize(0);
		vk.Persist(1);
		vk = "jas 0:0";
		cout << vk << ":\n";
		mhc->SetKey(vk);
		cout << (const char *) mhc->Key() << ":\n";
		cout << (const char *) *mhc << "\n";
	}
	  */
	return 0;
}


