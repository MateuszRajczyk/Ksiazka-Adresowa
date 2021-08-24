    #include "PlikTekstowy.h"

    string PlikTekstowy::pobierzNazwePlikuZUzytkownikami()
    {
        return NAZWA_PLIKU_Z_UZYTKOWNIKAMI;
    }

    string PlikTekstowy::pobierzNazwePlikuZAdresatami()
    {
        return NAZWA_PLIKU_Z_ADRESATAMI;
    }

    bool PlikTekstowy::czyPlikJestPusty(const string nazwaPliku)
    {
        if (ifstream(nazwaPliku, ios::ate).tellg())
            return false;
        else
            return true;
    }
