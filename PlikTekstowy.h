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
    const string NAZWA_PLIKU;

public:

    PlikTekstowy(string nazwaPliku) : NAZWA_PLIKU(nazwaPliku) {
    }

    string pobierzNazwePliku();

    bool czyPlikJestPusty(const string nazwaPliku);

};

#endif
