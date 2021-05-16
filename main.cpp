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

struct Recipient
{
    int idRecipient;
    int givenIdUser;
    string name;
    string lastName;
    string phoneNumber;
    string email;
    string address;
};

struct User
{
    int idUser;
    string userName;
    string userPassword;
};

int newPerson(vector<Recipient>&recipients, Recipient downloaded1, int &idRecipient, int &givenIdUser)
{
    string name, lastName, phoneNumber, email, address;
    fstream saveFile;

    saveFile.open("Adresaci.txt", ios::out | ios::app);

    cout<<"Podaj imie (lub imiona): ";
    cin.sync();
    getline(cin,name);

    cout<<"Podaj nazwisko: ";
    cin>>lastName;

    int i = 0;
    while(i < recipients.size())
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

    downloaded1.name = name;
    downloaded1.lastName = lastName;
    downloaded1.phoneNumber = phoneNumber;
    downloaded1.email = email;
    downloaded1.address = address;
    downloaded1.givenIdUser = givenIdUser;

    if(idRecipient == 0)
    {
        downloaded1.idRecipient = 1;
    }
    else
    {
        downloaded1.idRecipient = idRecipient + 1;
    }

    recipients.push_back(downloaded1);

    cout << "Stworzono nowa osobe" << endl;

    saveFile << recipients[recipients.size()-1].idRecipient << "|" << recipients[recipients.size()-1].givenIdUser << "|" << recipients[recipients.size()-1].name << "|" << recipients[recipients.size()-1].lastName << "|" << recipients[recipients.size()-1].phoneNumber << "|" << recipients[recipients.size()-1].email << "|" << recipients[recipients.size()-1].address << "|" << endl;

    idRecipient = idRecipient + 1;

    saveFile.close();
    Sleep(1000);

    return idRecipient;
}

void showRecipients (int &givenRecipient , vector<Recipient>&recipients)
{
    cout << recipients[givenRecipient].idRecipient << endl;
    cout << recipients[givenRecipient].name << endl;
    cout << recipients[givenRecipient].lastName << endl;
    cout << recipients[givenRecipient].phoneNumber << endl;
    cout << recipients[givenRecipient].email << endl;
    cout << recipients[givenRecipient].address << endl;
    cout << " " << endl;
}
void searchByName(vector<Recipient>&recipients, int &idRecipient)
{
    string name;

    cout << "Podaj imie szukanej osoby: ";
    cin >> name;

    cout << endl;

    int counter = 0;

    int j = 0;
    while(j < idRecipient)
    {
        if(recipients[j].name == name)
        {
            showRecipients(j, recipients);
            counter++;
        }
        j++;
    }
    if(counter == 0)
    {
        cout << "Nie ma osoby o takim imieniu" << endl;
    }
}

void searchByLastName(vector<Recipient>&recipients,  int &idRecipient)
{
    string lastName;

    cout << "Podaj nazwisko szukanej osoby: ";
    cin >> lastName;

    cout << endl;

    int counter = 0;

    int j = 0;
    while(j < idRecipient)
    {
        if(recipients[j].lastName == lastName)
        {
            showRecipients(j, recipients);
            counter++;
        }
        j++;
    }
    if(counter == 0)
    {
        cout << "Nie ma osoby o takim nazwisku" << endl;
    }
}

void searchEveryone(vector<Recipient>&recipients,  int &idRecipient)
{
    int k = 0;
    while(k < recipients.size())
    {
        showRecipients(k, recipients);
        k++;
    }
    if(recipients.size() == 0)
    {
        cout << "Skrzynka adresowa jest pusta" << endl;
    }
}

int readingIdRecipientsFromFile(int &allLines, int &idRecipient)
{
    fstream loadingFile;
    string line, part;
    int amountLines = 0;

    loadingFile.open("Adresaci.txt", ios::in);

    while(getline(loadingFile,line))
    {
        amountLines++;

        if(amountLines == allLines)
        {
            for(int g = 0; g < (line.length()); g++)
            {
                if((int)line[g] != 124)
                {
                    part += charToString(line[g]);
                }
                else if((int)line[g] == 124)
                {
                    idRecipient = stringToInt(part);
                    part.clear();
                    break;
                }
            }
        }
    }

    loadingFile.close();

    return idRecipient;
}

int loadingPeople(vector<Recipient>&recipients, Recipient downloaded1, int &idRecipient, int &givenIdUser)
{
    string line;
    string part;
    fstream loadingFile;
    int allLines = 0;

    recipients.clear();

    loadingFile.open("Adresaci.txt", ios::in);

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
                    downloaded1.idRecipient = stringToInt(part);
                    part.clear();
                }
                else if(wordsCounter == 1)
                {
                    downloaded1.givenIdUser = stringToInt(part);
                    part.clear();
                }
                else if(wordsCounter == 2)
                {
                    downloaded1.name = part;
                    part.clear();
                }
                else if(wordsCounter == 3)
                {
                    downloaded1.lastName = part;
                    part.clear();
                }
                else if(wordsCounter == 4)
                {
                    downloaded1.phoneNumber = part;
                    part.clear();
                }
                else if(wordsCounter == 5)
                {
                    downloaded1.email = part;
                    part.clear();
                }
                else if(wordsCounter == 6)
                {
                    downloaded1.address = part;
                    part.clear();
                }
                wordsCounter++;
            }
        }

        if (givenIdUser == downloaded1.givenIdUser)
        {
            recipients.push_back(downloaded1);
        }
        allLines++;
    }
    loadingFile.close();

    idRecipient = readingIdRecipientsFromFile(allLines, idRecipient);

    return idRecipient;
}

int loadingUsers(vector<User>&users, User downloaded2, int &idUser)
{
    string line;
    string part;
    fstream loadingFile;

    loadingFile.open("Uzytkownicy.txt", ios::in);

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
                    downloaded2.idUser = stringToInt(part);
                    part.clear();
                }
                else if(wordsCounter == 1)
                {
                    downloaded2.userName = part;
                    part.clear();
                }
                else if(wordsCounter == 2)
                {
                    downloaded2.userPassword = part;
                    part.clear();
                }
                wordsCounter++;
            }
        }
        users.push_back(downloaded2);
    }
    idUser = users.size();
    loadingFile.close();

    return idUser;
}

int delateRecipient(vector<Recipient>&recipients, int &idRecipient, int &givenIdUser, Recipient &downloaded1 )
{
    int positionNumber;

    string line, part;

    int idRecipientOldFile;

    fstream oldFile, newFile;

    int k = 0;
    while(k < recipients.size())
    {
        showRecipients(k, recipients);
        k++;
    }

    cout<<"Podaj numer pozycji adresata na liscie do usuniecia: ";
    cin>>positionNumber;

    int checkPositionNumber = 0;
    int f = 0;
    while(f < recipients.size())
    {
        if((positionNumber == recipients[f].idRecipient))
        {
            checkPositionNumber++;

            cout << "Czy napewno chcesz usunac wybranego adresata?" << endl;
            cout << "Wcisnij klawisz 't' aby potwierdzic. W przeciwnym wypadku wcisnij dowolny inny klawisz" << endl;
            cout << "Twoj wybor: ";

            char znak;
            cin >> znak;

            if(znak == 't')
            {
                recipients.erase(recipients.begin() + f);

                oldFile.open("Adresaci.txt", ios :: in);

                newFile.open("Adresaci_tymczasowy.txt", ios::out | ios::app);

                while(getline(oldFile,line))
                {
                    for(int g = 0; g < (line.length()); g++)
                    {

                        if((int)line[g] != 124)
                        {
                            part += charToString(line[g]);
                        }
                        else if(((int)line[g] == 124))
                        {
                            idRecipientOldFile = stringToInt(part);
                            part.clear();

                            if(idRecipientOldFile == positionNumber)
                            {
                                break;
                            }
                            else
                            {
                                newFile << line << endl;
                                break;
                            }
                        }
                    }
                }

                newFile.close();
                oldFile.close();

                remove ("Adresaci.txt");

                rename("Adresaci_tymczasowy.txt", "Adresaci.txt");

            }
        }
        f++;
    }

    if (checkPositionNumber == 0)
    {
        cout << "Nie ma adresata o takim numerze" << endl;
        system ("pause");

        return 1;
    }

    loadingPeople(recipients, downloaded1, idRecipient, givenIdUser);

    idRecipient = recipients.back().idRecipient;

    return idRecipient;
}

int editRecipient (vector<Recipient>&recipients, Recipient downloaded1, int &idRecipient)
{
    string newName, newLastName, newPhoneNumber, newEmail, newAddress;

    int positionNumber;

    char editChoice;

    cin >> editChoice;

    if(editChoice == '6')
    {
        return 1;
    }
    else
    {
        int k = 0;
        while(k < recipients.size())
        {
            showRecipients(k, recipients);
            k++;
        }

        cout << "Podaj numer pozycji adresata na liscie do edycji: ";
        cin >> positionNumber;
    }

    int checkPositionNumber = 0;

    int a = 0;
    while(a < recipients.size())
    {
        if((positionNumber == recipients[a].idRecipient))
        {
            checkPositionNumber++;

            if(editChoice == '1')
            {
                cout << "Podaj nowe imie (lub imiona): ";

                cin.sync();
                getline(cin,newName);

                recipients[a].name = newName;
            }
            else if(editChoice == '2')
            {
                cout << "Podaj nowe nazwisko: ";

                cin.sync();
                getline(cin,newLastName);

                recipients[a].lastName = newLastName;
            }
            else if(editChoice == '3')
            {
                cout << "Podaj nowy numer telefonu: ";

                cin.sync();
                getline(cin,newPhoneNumber);

                recipients[a].phoneNumber = newPhoneNumber;
            }
            else if(editChoice == '4')
            {
                cout << "Podaj nowy adres email: ";

                cin >> newEmail;

                recipients[a].email = newEmail;
            }
            else if(editChoice == '5')
            {
                cout << "Podaj nowy adres: ";

                cin.sync();
                getline(cin,newAddress);

                recipients[a].address = newAddress;
            }
            break;
        }
        a++;
    }

    if(checkPositionNumber == 0)
    {
        cout << "Nie ma adresata o takim numerze" << endl;
        system ("pause");

        return 1;
    }

    string line, part;

    int idRecipientOldFile;

    fstream oldFile, newFile;

    oldFile.open("Adresaci.txt", ios :: in);

    newFile.open("Adresaci_tymczasowy.txt", ios::out | ios::app);

    while(getline(oldFile,line))
    {
        for(int g = 0; g < (line.length()); g++)
        {

            if((int)line[g] != 124)
            {
                part += charToString(line[g]);
            }
            else if(((int)line[g] == 124))
            {
                idRecipientOldFile = stringToInt(part);

                part.clear();

                if(idRecipientOldFile == positionNumber)
                {
                    int j = 0;
                    while(j < recipients.size())
                    {
                        if((positionNumber == recipients[j].idRecipient))
                        {
                            newFile << recipients[j].idRecipient << "|" << recipients[j].givenIdUser << "|" << recipients[j].name << "|" << recipients[j].lastName << "|" << recipients[j].phoneNumber << "|" << recipients[j].email << "|" << recipients[j].address << "|" << endl;
                        }
                        j++;
                    }
                    break;
                }
                else
                {
                    newFile << line << endl;
                    break;
                }
            }
        }
    }

    newFile.close();
    oldFile.close();

    remove ("Adresaci.txt");

    rename("Adresaci_tymczasowy.txt", "Adresaci.txt");
}

int registerUser(vector<User>&users, User downloaded2, int &idUser)
{
    string userName, userPassword;
    fstream saveUsers;

    saveUsers.open("Uzytkownicy.txt", ios::out | ios::app);

    cout << "Podaj nazwe uzytkownika: ";
    cin.sync();
    getline(cin,userName);

    cout << "Podaj haslo: ";
    cin.sync();
    getline(cin,userPassword);

    int i = 0;
    while(i < idUser)
    {
        if(users[i].userName == userName)
        {
            cout << "Taki uzytkownik juz istnieje. Wpisz inna nazwe uzytkownika" << endl;
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
                cout << "Podaj nazwe uzytkownika: ";
                cin.sync();
                getline(cin,userName);

                cout<<"Podaj haslo: ";
                cin.sync();
                getline(cin,userPassword);

                i = 0;
            }
        }
        else
        {
            i++;
        }
    }

    downloaded2.userName = userName;
    downloaded2.userPassword = userPassword;

    if(idUser == 0)
    {
        downloaded2.idUser = 1;
    }
    else
    {
        downloaded2.idUser = users.back().idUser + 1;
    }

    users.push_back(downloaded2);

    cout << "Stworzono nowego uzytkownika" << endl;

    saveUsers << users[idUser].idUser << "|" << users[idUser].userName << "|" << users[idUser].userPassword << "|" << endl;

    idUser = idUser + 1;

    saveUsers.close();
    Sleep(1000);

    return idUser;
}

void changePassword(vector<User>&users, int &givenIdUser)
{
    string newPassword;
    fstream saveNewPassword;

    cout << "Podaj nowe haslo:";
    cin >> newPassword;

    users[givenIdUser-1].userPassword = newPassword;

    saveNewPassword.open("Uzytkownicy.txt", ios :: out);

    int givenPlace = 0;

    while(givenPlace < users.size())
    {
        saveNewPassword << users[givenPlace].idUser << "|" << users[givenPlace].userName << "|" << users[givenPlace].userPassword << "|" << endl;
        givenPlace++;
    }
    saveNewPassword.close();
}

void mainLoadingUsers (User &downloaded2, vector<User>&users, int &idUser)
{
    fstream loadingFile;

    loadingFile.open("Uzytkownicy.txt", ios::in);

    if(loadingFile.good() == false)
    {
        idUser = 0;
    }
    else
    {
        idUser = loadingUsers(users, downloaded2, idUser);
    }

    loadingFile.close();
}

void menuActionAtRecipients(vector<User>users, int i)
{
    system("cls");

    cout << "Zalogowany jako: " << users[i].userName << endl;
    cout << endl;
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow" << endl;
    cout << "5. Usun adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "7. Zmien haslo" << endl;
    cout << "8. Wyloguj sie" << endl;
    cout << "Twoj wybor: ";
}

void menuEditRecipient ()
{
    system("cls");

    cout << "1 - imie" << endl;
    cout << "2 - nazwisko" << endl;
    cout << "3 - numer telefonu" << endl;
    cout << "4 - email" << endl;
    cout << "5 - adres" << endl;
    cout << "6 - powrot do menu" << endl;
    cout << "Twoj wybor: ";
}
void mainLoadingRecipients (vector<Recipient>&recipients, Recipient &downloaded1, int &idRecipient, int &givenIdUser)
{
    fstream loadingFile;

    loadingFile.open("Adresaci.txt", ios::in);

    if(loadingFile.good() == false)
    {
        idRecipient = 0;
    }
    else if(idRecipient == 0)
    {
        idRecipient = loadingPeople(recipients, downloaded1, idRecipient, givenIdUser);
    }

    loadingFile.close();
}

void opctionsLoginRecipients (vector<User>&users, vector<Recipient>&recipients, Recipient &downloaded1, int &idRecipient, int &givenIdUser, char choice)
{
    if(choice == '1')
    {
        idRecipient = newPerson(recipients, downloaded1, idRecipient, givenIdUser);
    }
    else if(choice == '2')
    {
        searchByName(recipients, idRecipient);
        cout << endl;
        system("pause");
    }
    else if(choice == '3')
    {
        searchByLastName(recipients, idRecipient);
        cout << endl;
        system("pause");
    }
    else if(choice == '4')
    {
        searchEveryone(recipients, idRecipient);
        cout << endl;
        system("pause");
    }
    else if(choice == '5')
    {
        idRecipient = delateRecipient(recipients, idRecipient ,givenIdUser, downloaded1);
        cout << endl;
    }
    else if(choice == '6')
    {
        int positionNumber;

        menuEditRecipient();

        editRecipient(recipients, downloaded1, idRecipient);

        cout << endl;
    }
    else if(choice == '7')
    {
        changePassword(users, givenIdUser);
    }
}

void loginSystem (vector<User>&users, vector<Recipient>&recipients, int &idUser, Recipient downloaded1, char &choice)
{
    string userName, userPassword;
    int idRecipient = 0;
    char logInAgain;

    int c = 3;
    while(c > 0)
    {
        cout << "Podaj nazwe uzytkownika: ";
        cin.sync();
        getline(cin,userName);

        cout << "Podaj haslo: ";
        cin.sync();
        getline(cin,userPassword);

        int checkData = 0;

        int j = 0;
        while(j < idUser)
        {
           if((users[j].userName == userName) && (users[j].userPassword == userPassword))
           {
                checkData++;
           }
           j++;
        }

        if(checkData == 0)
        {
            if(c > 1)
            {
                cout << "Bledny login lub haslo" << endl;
                cout << "Pozostalo prob: " << c-1 << endl;
                cout << "Jesli chcesz sprobowac jeszcze raz wcisnij 't'. Aby wyjsc do menu wcisnij dowolny inny klawisz." << endl;
                cout << "Twoj wybor: ";
                cin >> logInAgain;

                if(logInAgain != 't')
                {
                    break;
                }
            }
            else
            {
                cout << "Bledny login lub haslo" << endl;
                cout << "Wykorzystano limit logowania. Odczekaj 20 sekund" << endl;
                Sleep(20000);
            }
        }
        else
        {
            break;
        }

        c--;
    }

    int i = 0;
    while(i < idUser)
    {
        if((users[i].userName == userName) && (users[i].userPassword == userPassword))
        {

            int givenIdUser = users[i].idUser;

            mainLoadingRecipients(recipients, downloaded1, idRecipient, givenIdUser);

            while(true)
            {
                menuActionAtRecipients(users, i);

                cin >> choice;

                if(choice == '8')
                {
                    break;
                }
                else
                {
                    opctionsLoginRecipients(users, recipients, downloaded1, idRecipient, givenIdUser, choice);
                }
            }
            break;
        }
        else
        {
            i++;
        }
    }
}

int main()
{
    vector<Recipient>recipients;

    vector<User>users;

    Recipient downloaded1;

    User downloaded2;

    int idUser = 0;

    mainLoadingUsers(downloaded2, users, idUser);

    char choice;
    char userChoice;

    while(true)
    {
        system("cls");
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "3. Zamknij program" << endl;
        cout << "Twoj wybor: ";

        cin >> userChoice;

        if(userChoice == '1')
        {
            loginSystem(users,recipients, idUser, downloaded1, choice);
        }
        else if(userChoice == '2')
        {
            idUser = registerUser(users, downloaded2, idUser);
        }
        else if(userChoice == '3')
        {
            exit(0);
        }
    }

    return 0;
}
