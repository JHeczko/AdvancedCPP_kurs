/*
*3. Zaimplementuj szablon funkcji SongFactory
* tak aby obiekt ‘song’ był wskaźnikiem typu unique_ptr
* dla obiektów klasy Song
*
* auto song = SongFactory(L"Michael Jackson", L"Beat It");
*
* oraz przedstaw działanie konstruktora i destruktora obiektu przechowywanego
* przez wskaźnik we wnętrzu inteligentnego wskaźnika. Wypełnij
* std::vector<std::unique_ptr<Song>> songs i pokaż, że zakresowa pętla „for”
* musi wykorzystywać referencje.
* */

#include <iostream>
#include <memory>

using namespace std;

