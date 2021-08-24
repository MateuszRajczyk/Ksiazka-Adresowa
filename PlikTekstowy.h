#ifndef PLIKTEKSTOWY_H
#define PLIKTEKSTOWY_H

#include <iostream>
#include <vector>
#include "Adresat.h"
#include <fstream>
#include <cstdlib>
#include <string>
#include "MetodyPomocnicze.h"
#include <sstream>
#include <algorithm>
#include <windows.h>

using namespace std;

class PlikTekstowy
{
    const string NAZWA_PLIKU_Z_UZYTKOWNIKAMI;
    const string NAZWA_PLIKU_Z_ADRESATAMI;

public:

    PlikTekstowy(string nazwaPlikuZUzytkownikami, string nazwaPlikuZAdresatami) : NAZWA_PLIKU_Z_UZYTKOWNIKAMI(nazwaPlikuZUzytkownikami), NAZWA_PLIKU_Z_ADRESATAMI(nazwaPlikuZAdresatami) {
    }

    string pobierzNazwePlikuZUzytkownikami();

    string pobierzNazwePlikuZAdresatami();

    bool czyPlikJestPusty(const string nazwaPliku);

};

#endif
