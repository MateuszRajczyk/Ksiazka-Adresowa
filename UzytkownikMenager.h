#ifndef UZYTKOWNIKMENAGER_H
#define UZYTKOWNIKMENAGER_H

#include <iostream>
#include <vector>
#include "Uzytkownik.h"
#include <windows.h>
#include <fstream>
#include <sstream>
#include "PlikZUzytkownikami.h"
#include "MetodyPomocnicze.h"


using namespace std;

class UzytkownikMenager
{
    int idZalogowanegoUzytkownika;
    vector<Uzytkownik>uzytkownicy;
    PlikZUzytkownikami plikZUzytkownikami;
    Uzytkownik uzytkownik;

    Uzytkownik podajDaneNowegoUzytkownika();
    int pobierzIdNowegoUzytkownika();
    bool czyIstniejeLogin(string login);
public:
    UzytkownikMenager(string nazwaPlikuZUzytkownikami, int idZalogowanegoUzytkownika = 0) : plikZUzytkownikami(nazwaPlikuZUzytkownikami), idZalogowanegoUzytkownika(idZalogowanegoUzytkownika) {
        idZalogowanegoUzytkownika = 0;
        uzytkownicy = plikZUzytkownikami.wczytajUzytkownikowZPliku();
    };
    void rejestracjaUzytkownika();
    void wypiszWszystkichUzytkownikow();
    int logowanieUzytkownika();
    int pobierzIdZalogowanegoUzytkownika();
    void ustawIdZalogowanegoUzytkownika(int noweId);
    char wczytajZnak();
    bool czyUzytkownikJestZalogowany();
    void wylogowanieUzytkownika();
    void zmianaHaslaZalogowanegoUzytkownika();

};

#endif
