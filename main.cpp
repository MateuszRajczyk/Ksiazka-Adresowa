#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <conio.h>
#include <algorithm>

using namespace std;

string charToString(char sign)
{
    string s;
    stringstream ss;
    ss << sign;
    ss >> s;
    return s;
}

int stringToInt(string word)
{
    int i;
    istringstream iss(word);
    iss >> i;
    return i;
}

struct Person
{
    int id;
    string name;
    string lastName;
    string phoneNumber;
    string email;
    string address;
};

int newPerson(vector<Person>&recipients, Person downloaded, int &idPerson)
{
    string name, lastName, phoneNumber, email, address;
    fstream saveFile;

    saveFile.open("Ksiazka adresowa.txt", ios::out | ios::app);

    cout<<"Podaj imie (lub imiona): ";
    cin.sync();
    getline(cin,name);

    cout<<"Podaj nazwisko: ";
    cin>>lastName;

    int i = 0;
    while(i < idPerson)
    {
        if((recipients[i].name == name) && (recipients[i].lastName == lastName))
        {
            cout << "Taka osoba juz istnieje. Wpisz inne imie i nazwisko osoby." << endl;
            cout << "Aby wyjsc do menu glownego wcisnij '1', aby kontynuowac wcisnij dowolny inny klawisz"<<endl;
            cout << "Twoj wybor:";

            char choice;

            cin >> choice;

            if(choice == '1')
            {
                return 0;
            }
            else if(choice != '1')
            {
                cout << "Podaj imie: ";
                cin.sync();
                getline(cin,name);

                cout<<"Podaj nazwisko: ";
                cin>>lastName;

                i = 0;
            }
        }
        else
        {
            i++;
        }
    }

    cout<<"Podaj nr telefonu: ";
    cin.sync();
    getline(cin,phoneNumber);

    cout<<"Podaj adres email: ";
    cin>>email;

    cout<<"Podaj adres: ";
    cin.sync();
    getline(cin,address);

    downloaded.name = name;
    downloaded.lastName = lastName;
    downloaded.phoneNumber = phoneNumber;
    downloaded.email = email;
    downloaded.address = address;

    if(idPerson == 0)
    {
        downloaded.id = 1;
    }
    else
    {
        downloaded.id = recipients.back().id + 1;
    }

    recipients.push_back(downloaded);

    cout << "Stworzono nowa osobe" << endl;

    saveFile << recipients[idPerson].id << "|" << recipients[idPerson].name << "|" << recipients[idPerson].lastName << "|" << recipients[idPerson].phoneNumber << "|" << recipients[idPerson].email << "|" << recipients[idPerson].address << "|" << endl;

    idPerson = idPerson + 1;

    saveFile.close();
    Sleep(1000);

    return idPerson;
}

void searchByName(vector<Person>&recipients, int &idPerson)
{
    string name;

    cout << "Podaj imie szukanej osoby: ";
    cin >> name;

    cout << endl;

    int counter = 0;

    int j = 0;
    while(j < idPerson)
    {
        if(recipients[j].name == name)
        {
            cout << recipients[j].id << endl;
            cout << recipients[j].name << endl;
            cout << recipients[j].lastName << endl;
            cout << recipients[j].phoneNumber << endl;
            cout << recipients[j].email << endl;
            cout << recipients[j].address << endl;
            cout << " " << endl;
            counter++;
        }
        j++;
    }
    if(counter == 0)
    {
        cout << "Nie ma osoby o takim imieniu" << endl;
    }
}

void searchByLastName(vector<Person>&recipients,  int &idPerson)
{
    string lastName;

    cout << "Podaj nazwisko szukanej osoby: ";
    cin >> lastName;

    cout << endl;

    int counter = 0;

    int j = 0;
    while(j < idPerson)
    {
        if(recipients[j].lastName == lastName)
        {
            cout << recipients[j].id << endl;
            cout << recipients[j].name << endl;
            cout << recipients[j].lastName << endl;
            cout << recipients[j].phoneNumber << endl;
            cout << recipients[j].email << endl;
            cout << recipients[j].address << endl;
            cout << " " << endl;
            counter++;
        }
        j++;
    }
    if(counter == 0)
    {
        cout << "Nie ma osoby o takim nazwisku" << endl;
    }
}

void searchEveryone(vector<Person>&recipients,  int &idPerson)
{
    int k = 0;
    while(k < recipients.size())
    {
        cout << recipients[k].id << endl;
        cout << recipients[k].name << endl;
        cout << recipients[k].lastName << endl;
        cout << recipients[k].phoneNumber << endl;
        cout << recipients[k].email << endl;
        cout << recipients[k].address << endl;
        cout << " " << endl;
        k++;
    }
    if(recipients.size() == 0)
    {
        cout << "Skrzynka adresowa jest pusta" << endl;
    }
}

int loadingPeople(vector<Person>&recipients, Person downloaded, int &idPerson)
{
    string line;
    string part;
    fstream loadingFile;

    loadingFile.open("Ksiazka adresowa.txt", ios::in);

    while(getline(loadingFile,line))
    {
        int wordsCounter = 0;

        for(int g = 0; g < (line.length()); g++)
        {
            if((int)line[g] != 124)
            {
                part += charToString(line[g]);
            }
            else if((int)line[g] == 124)
            {
                if(wordsCounter == 0)
                {
                    downloaded.id = stringToInt(part);
                    part.clear();
                }
                else if(wordsCounter == 1)
                {
                    downloaded.name = part;
                    part.clear();
                }
                else if(wordsCounter == 2)
                {
                    downloaded.lastName = part;
                    part.clear();
                }
                else if(wordsCounter == 3)
                {
                    downloaded.phoneNumber = part;
                    part.clear();
                }
                else if(wordsCounter == 4)
                {
                    downloaded.email = part;
                    part.clear();
                }
                else if(wordsCounter == 5)
                {
                    downloaded.address = part;
                    part.clear();
                }
                wordsCounter++;
            }
        }
        recipients.push_back(downloaded);
    }
    idPerson = recipients.size();
    loadingFile.close();

    return idPerson;
}

int delateRecipient(vector<Person>&recipients, int &idPerson)
{
    int positionNumber;

    int k = 0;
    while(k < recipients.size())
    {
        cout << recipients[k].id << endl;
        cout << recipients[k].name << endl;
        cout << recipients[k].lastName << endl;
        cout << recipients[k].phoneNumber << endl;
        cout << recipients[k].email << endl;
        cout << recipients[k].address << endl;
        cout << " " << endl;
        k++;
    }

    cout<<"Podaj numer pozycji adresata na liscie do usuniecia: ";
    cin>>positionNumber;

    int f = 0;
    while(f < recipients.size())
    {
        if((positionNumber == recipients[f].id))
        {
            cout << "Czy napewno chcesz usunac wybranego adresata?" << endl;
            cout << "Wcisnij klawisz 't' aby potwierdzic. W przeciwnym wypadku wcisnij dowolny inny klawisz" << endl;
            cout << "Twoj wybor: ";

            char znak;
            cin >> znak;

            if(znak == 't')
            {
                recipients.erase(recipients.begin() + f);

                fstream delateFromFile;

                delateFromFile.open("Ksiazka adresowa.txt", ios::out);

                idPerson = recipients.size();

                int d = 0;
                while(d < recipients.size())
                {
                    delateFromFile << recipients[d].id << "|" << recipients[d].name << "|" << recipients[d].lastName << "|" << recipients[d].phoneNumber << "|" << recipients[d].email << "|" << recipients[d].address << "|" << endl;
                    d++;
                }
                delateFromFile.close();
            }
        }
        f++;
    }
    return idPerson;
}

void editRecipient (vector<Person>&recipients, Person downloaded, int &idPerson)
{
    string newName, newLastName, newPhoneNumber, newEmail, newAddress;

    int positionNumber;

    char editChoice;

    cin >> editChoice;

    if(editChoice == '6')
    {
        return;
    }
    else
    {
        int k = 0;
        while(k < recipients.size())
        {
            cout << recipients[k].id << endl;
            cout << recipients[k].name << endl;
            cout << recipients[k].lastName << endl;
            cout << recipients[k].phoneNumber << endl;
            cout << recipients[k].email << endl;
            cout << recipients[k].address << endl;
            cout << " " << endl;
            k++;
        }

        cout << "Podaj numer pozycji adresata na liscie do edycji: ";
        cin >> positionNumber;
    }

    fstream replaceFile;

    replaceFile.open("Ksiazka adresowa.txt", ios::out);

    int a = 0;
    while(a < recipients.size())
    {
        if((positionNumber == recipients[a].id))
        {
            if(editChoice == '1')
            {
                cout << "Podaj nowe imie (lub imiona): ";

                cin.sync();
                getline(cin,newName);

                recipients[a].name = newName;

                int givenPlace = 0;
                while(givenPlace < recipients.size())
                {
                    replaceFile << recipients[givenPlace].id << "|" << recipients[givenPlace].name << "|" << recipients[givenPlace].lastName << "|" << recipients[givenPlace].phoneNumber << "|" << recipients[givenPlace].email << "|" << recipients[givenPlace].address << "|" << endl;
                    givenPlace++;
                }
            }
            else if(editChoice == '2')
            {
                cout << "Podaj nowe nazwisko: ";

                cin.sync();
                getline(cin,newLastName);

                recipients[a].lastName = newLastName;

                int givenPlace = 0;
                while(givenPlace < recipients.size())
                {
                    replaceFile << recipients[givenPlace].id << "|" << recipients[givenPlace].name << "|" << recipients[givenPlace].lastName << "|" << recipients[givenPlace].phoneNumber << "|" << recipients[givenPlace].email << "|" << recipients[givenPlace].address << "|" << endl;
                    givenPlace++;
                }

            }
            else if(editChoice == '3')
            {
                cout << "Podaj nowy numer telefonu: ";

                cin.sync();
                getline(cin,newPhoneNumber);

                recipients[a].phoneNumber = newPhoneNumber;

                int givenPlace = 0;
                while(givenPlace < recipients.size())
                {
                    replaceFile << recipients[givenPlace].id << "|" << recipients[givenPlace].name << "|" << recipients[givenPlace].lastName << "|" << recipients[givenPlace].phoneNumber << "|" << recipients[givenPlace].email << "|" << recipients[givenPlace].address << "|" << endl;
                    givenPlace++;
                }
            }
            else if(editChoice == '4')
            {
                cout << "Podaj nowy adres email: ";

                cin >> newEmail;

                recipients[a].email = newEmail;

                int givenPlace = 0;
                while(givenPlace < recipients.size())
                {
                    replaceFile << recipients[givenPlace].id << "|" << recipients[givenPlace].name << "|" << recipients[givenPlace].lastName << "|" << recipients[givenPlace].phoneNumber << "|" << recipients[givenPlace].email << "|" << recipients[givenPlace].address << "|" << endl;
                    givenPlace++;
                }
            }
            else if(editChoice == '5')
            {
                cout << "Podaj nowy adres: ";

                cin.sync();
                getline(cin,newAddress);

                recipients[a].address = newAddress;

                int givenPlace = 0;
                while(givenPlace < recipients.size())
                {
                    replaceFile << recipients[givenPlace].id << "|" << recipients[givenPlace].name << "|" << recipients[givenPlace].lastName << "|" << recipients[givenPlace].phoneNumber << "|" << recipients[givenPlace].email << "|" << recipients[givenPlace].address << "|" << endl;
                    givenPlace++;
                }
            }
            break;
        }
        a++;
    }
    replaceFile.close();
}

int main()
{
    vector<Person>recipients;

    Person downloaded;

    fstream loadingFile;

    int idPerson = 0;

    loadingFile.open("Ksiazka adresowa.txt", ios::in);

    if(loadingFile.good() == false)
    {
        idPerson = 0;

        cout << "Skrzynka adresowa jest pusta" << endl;

        Sleep(1000);
    }
    else
    {
        idPerson = loadingPeople(recipients, downloaded, idPerson);
    }

    loadingFile.close();

    char choice;

    while(true)
    {
        system("cls");
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po nameniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyszukaj wszystkich adresatow" << endl;
        cout << "5. Usun addressata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "7. Zakoncz program" << endl;
        cout << "Twoj wybor: ";

        cin >> choice;

        if(choice == '1')
        {
            idPerson = newPerson(recipients, downloaded, idPerson);
        }
        else if(choice == '2')
        {
            searchByName(recipients, idPerson);
            cout << endl;
            system("pause");
        }
        else if(choice == '3')
        {
            searchByLastName(recipients, idPerson);
            cout << endl;
            system("pause");
        }
        else if(choice == '4')
        {
            searchEveryone(recipients, idPerson);
            cout << endl;
            system("pause");
        }
        else if(choice == '5')
        {
            idPerson = delateRecipient(recipients, idPerson);
            cout << endl;
        }
        else if(choice == '6')
        {
            cout << "1 - imie" << endl;
            cout << "2 - nazwisko" << endl;
            cout << "3 - numer telefonu" << endl;
            cout << "4 - email" << endl;
            cout << "5 - adres" << endl;
            cout << "6 - powrot do menu" << endl;
            cout << "Twoj wybor: ";

            editRecipient(recipients, downloaded, idPerson);

            cout << endl;
        }
        else if(choice == '7')
        {
            exit(0);
        }
    }

    return 0;
}
