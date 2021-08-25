#ifndef ADRESATMENAGER_H
#define ADRESATMENAGER_H

#include <iostream>
#include <vector>
#include "Adresat.h"
#include <windows.h>
#include <fstream>
#include <sstream>
#include "PlikZAdresatami.h"
#include "MetodyPomocnicze.h"


using namespace std;

class AdresatMenager
{
    const int ID_ZALOGOWANEGO_UZYTKOWNIKA;
    vector <Adresat> adresaci;
    PlikZAdresatami plikZAdresatami;
    int idUsunietegoAdresata;

    Adresat podajDaneNowegoAdresata();
    void wyswietlDaneAdresata(Adresat adresat);

public:
    AdresatMenager(string nazwaPlikuZAdresatami, int idZalogowanegoUzytkownika)
        : plikZAdresatami(nazwaPlikuZAdresatami), ID_ZALOGOWANEGO_UZYTKOWNIKA(idZalogowanegoUzytkownika)
    {
        adresaci = plikZAdresatami.wczytajAdresatowZalogowanegoUzytkownikaZPliku(ID_ZALOGOWANEGO_UZYTKOWNIKA);
    };
    void dodajAdresata();
    void wyswietlWszystkichAdresatow();
    void wyszukajAdresatowPoImieniu();
    void wyszukajAdresatowPoNazwisku();
    void wyswietlIloscWyszukanychAdresatow(int iloscAdresatow);
    int usunAdresata();
    int usunWybranegoAdresata();
    int podajIdWybranegoAdresata();
    void edytujAdresata();
    char wybierzOpcjeZMenuEdycja();
};

#endif
