#ifndef KSIAZKAADRESOWA_H
#define KSIAZKAADRESOWA_H

#include <iostream>

#include "UzytkownikMenager.h"
#include "AdresatMenager.h"
#include "PlikZAdresatami.h"

using namespace std;

class KsiazkaAdresowa
{
    UzytkownikMenager uzytkownikMenager;
    AdresatMenager *adresatMenager;
    const string NAZWA_PLIKU_Z_ADRESATAMI;

public:
    KsiazkaAdresowa(string nazwaPlikuZUzytkownikami, string nazwaPlikuZAdresatami) : uzytkownikMenager(nazwaPlikuZUzytkownikami), NAZWA_PLIKU_Z_ADRESATAMI(nazwaPlikuZAdresatami)
    {
        adresatMenager = NULL;
    };
    ~KsiazkaAdresowa()
    {
        delete adresatMenager;
        adresatMenager = NULL;
    };
    void wypiszWszystkichUzytkownikow();
    void rejestracjaUzytkownika();
    char wybierzOpcjeZMenuUzytkownika();
    char wybierzOpcjeZMenuGlownego();
    void logowanieUzytkownika();
    int pobierzIdZalogowanegoUzytkownika();
    void dodajAdresata();
    void wyswietlWszystkichAdresatow();
    void wyszukajAdresatowPoImieniu();
    void wyszukajAdresatowPoNazwisku();
    void wylogowanieUzytkownika();
    void zmianaHaslaZalogowanegoUzytkownika();
    int usunAdresata();
    void edytujAdresata();


};

#endif
