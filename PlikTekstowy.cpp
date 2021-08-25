    #include "PlikTekstowy.h"

    string PlikTekstowy::pobierzNazwePliku()
    {
        return NAZWA_PLIKU;
    }

    bool PlikTekstowy::czyPlikJestPusty(const string nazwaPliku)
    {
        if (ifstream(nazwaPliku, ios::ate).tellg())
            return false;
        else
            return true;
    }
