#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Kontakt {
    int id = 0;
    string imie = "", nazwisko = "", numerTel = "", eMail = "", adresZamieszkania = "";
};

string wczytajLinie () {
    string wejscie = "";
    cin.sync();
    getline(cin, wejscie);

    return wejscie;
}

char wczytajZnak() {
    string wejscie = "";
    char znak = {0};

    while(true) {
        getline(cin, wejscie);

        if(wejscie.length() == 1) {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak! Wpisz ponownie: ";
    }

    return znak;
}

int wczytajLiczbeCalkowita() {
    string wejscie = "";
    int liczba = 0;

    while(true) {
        cin.sync();
        getline(cin, wejscie);

        stringstream myStream(wejscie);
        if (myStream >> liczba) {
            break;
        }

        cout << "To nie jest liczba! Wpisz ponownie: ";
    }
    return liczba;
}

void wczytajKsiazkeAdresowa (vector<Kontakt>& kontakty) {
    Kontakt daneKontaktowe;
    string liniaZKsiazkiAdresowej, daneKontaktoweStr;
    fstream ksiazkaAdresowa;

    ksiazkaAdresowa.open("Ksiazka_Adresowa.txt", ios::in);
    if(ksiazkaAdresowa.good()==true) {
        while(!ksiazkaAdresowa.eof()) {

            getline (ksiazkaAdresowa, liniaZKsiazkiAdresowej);

            if (liniaZKsiazkiAdresowej.find('|') != string::npos) {
                size_t separatorDanychWPliku = liniaZKsiazkiAdresowej.find('|');

                daneKontaktoweStr = liniaZKsiazkiAdresowej.substr(0, separatorDanychWPliku);
                daneKontaktowe.id = atoi(daneKontaktoweStr.c_str());
                liniaZKsiazkiAdresowej = liniaZKsiazkiAdresowej.erase(0, separatorDanychWPliku+1);

                separatorDanychWPliku = liniaZKsiazkiAdresowej.find('|');
                daneKontaktowe.imie = liniaZKsiazkiAdresowej.substr(0, separatorDanychWPliku);
                liniaZKsiazkiAdresowej = liniaZKsiazkiAdresowej.erase(0, separatorDanychWPliku+1);

                separatorDanychWPliku = liniaZKsiazkiAdresowej.find('|');
                daneKontaktowe.nazwisko = liniaZKsiazkiAdresowej.substr(0, separatorDanychWPliku);
                liniaZKsiazkiAdresowej = liniaZKsiazkiAdresowej.erase(0, separatorDanychWPliku+1);

                separatorDanychWPliku = liniaZKsiazkiAdresowej.find('|');
                daneKontaktowe.numerTel = liniaZKsiazkiAdresowej.substr(0, separatorDanychWPliku);
                liniaZKsiazkiAdresowej = liniaZKsiazkiAdresowej.erase(0, separatorDanychWPliku+1);

                separatorDanychWPliku = liniaZKsiazkiAdresowej.find('|');
                daneKontaktowe.eMail = liniaZKsiazkiAdresowej.substr(0, separatorDanychWPliku);
                liniaZKsiazkiAdresowej = liniaZKsiazkiAdresowej.erase(0, separatorDanychWPliku+1);

                separatorDanychWPliku = liniaZKsiazkiAdresowej.find('|');
                daneKontaktowe.adresZamieszkania = liniaZKsiazkiAdresowej.substr(0, separatorDanychWPliku);
                liniaZKsiazkiAdresowej = liniaZKsiazkiAdresowej.erase(0, separatorDanychWPliku+1);

                kontakty.push_back(daneKontaktowe);
            }
        }
    }
    ksiazkaAdresowa.close();
}

void dodajKontaktDoPliku (Kontakt daneKontaktowe) {
    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("Ksiazka_Adresowa.txt", ios::out | ios::app);
    if(ksiazkaAdresowa.good()==true) {
        ksiazkaAdresowa << daneKontaktowe.id << "|";
        ksiazkaAdresowa << daneKontaktowe.imie << "|";
        ksiazkaAdresowa << daneKontaktowe.nazwisko <<"|";
        ksiazkaAdresowa << daneKontaktowe.numerTel << "|";
        ksiazkaAdresowa << daneKontaktowe.eMail << "|";
        ksiazkaAdresowa << daneKontaktowe.adresZamieszkania << "|" << endl;
    }
    ksiazkaAdresowa.close();
}

int dodajKontakt (vector<Kontakt>& kontakty, int liczbaKontaktow) {
    Kontakt daneKontaktowe;
    vector <Kontakt>::iterator it;

    system("cls");
    cout << "Podaj imie: ";
    daneKontaktowe.imie = wczytajLinie();
    cout << "Podaj nazwisko: ";
    daneKontaktowe.nazwisko = wczytajLinie();
    cout << "Podaj nr telefonu: ";
    daneKontaktowe.numerTel = wczytajLinie();
    cout << "Podaj adres e-mail: ";
    daneKontaktowe.eMail  = wczytajLinie();
    cout << "Podaj adres zamieszkania: ";
    daneKontaktowe.adresZamieszkania = wczytajLinie();

    liczbaKontaktow++;

    if (kontakty.size() == 0) {
        daneKontaktowe.id = liczbaKontaktow;
    } else {
        daneKontaktowe.id = kontakty.back().id + 1;
    }
    kontakty.push_back(daneKontaktowe);
    dodajKontaktDoPliku (daneKontaktowe);

    cout << "Dodano kontakt do ksiazki adresowej." << endl;
    Sleep(1000);
    return liczbaKontaktow;
}

void wyszukajKontaktPoImieniu (vector<Kontakt>& kontakty) {
    string imie;
    int nieZnalezionoImienia = 0;

    cout << "Podaj imie do wyszukania kontaktu: ";
    imie = wczytajLinie();

    for (int i = 0; i < kontakty.size(); i++) {
        if (kontakty[i].imie == imie) {
            cout << "\nId kontaktu: " << kontakty[i].id << endl;
            cout << "Imie: " << kontakty[i].imie << endl;
            cout << "Nazwisko: "<< kontakty[i].nazwisko << endl;
            cout << "Nr telefonu: " << kontakty[i].numerTel << endl;
            cout << "E-mail: " << kontakty[i].eMail << endl;
            cout << "Adres zamieszkania: " << kontakty[i].adresZamieszkania << endl;
        } else {
            nieZnalezionoImienia++;
            if (nieZnalezionoImienia == kontakty.size()) {
                cout << "Brak takiego kontaktu do wyswietlenia!" << endl;
            }
        }
    }
    system ("pause");
}

void wyszukajKontaktPoNazwisku (vector<Kontakt>& kontakty) {
    string nazwisko;
    int nieZnalezionoNazwiska = 0;

    cout << "Podaj nazwisko do wyszukania kontaktu: ";
    nazwisko = wczytajLinie();

    for (int i = 0; i < kontakty.size(); i++) {
        if (kontakty[i].nazwisko == nazwisko) {
            cout << '\n' << "Id kontaktu: " << kontakty[i].id << endl;
            cout << "Nazwisko: " << kontakty[i].nazwisko << endl;
            cout << "Imie: " << kontakty[i].imie << endl;
            cout << "Nr telefonu: " << kontakty[i].numerTel << endl;
            cout << "E-mail: " << kontakty[i].eMail << endl;
            cout << "Adres zamieszkania: " << kontakty[i].adresZamieszkania << endl;
        } else {
            nieZnalezionoNazwiska++;
            if (nieZnalezionoNazwiska == kontakty.size()) {
                cout << "Brak takiego kontaktu do wyswietlenia!" << endl;
            }
        }
    }
    system ("pause");
}

void wyswietlListeWszystkichKontaktow (vector<Kontakt>& kontakty) {
    fstream ksiazkaAdresowa;
    string liniaZKsiazkiAdresowej;

    ksiazkaAdresowa.open("Ksiazka_Adresowa.txt", ios::in);
    for (int i = 0; i < kontakty.size(); i++) {
        cout << "\nId kontaktu: " << kontakty[i].id << endl;
        cout << "Imie: " << kontakty[i].imie << endl;
        cout << "Nazwisko: "<< kontakty[i].nazwisko << endl;
        cout << "Nr telefonu: " << kontakty[i].numerTel << endl;
        cout << "E-mail: " << kontakty[i].eMail << endl;
        cout << "Adres zamieszkania: " << kontakty[i].adresZamieszkania << endl;
    }
    ksiazkaAdresowa.close();

    system ("pause");
}

void uaktualnijKsiazkeAdresowaPoEdycji (vector<Kontakt>& kontakty) {

    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("Ksiazka_Adresowa.txt", ios::out);
    if(ksiazkaAdresowa.good()==true) {
        for (int i = 0; i < kontakty.size(); i++) {

            ksiazkaAdresowa << kontakty[i].id << "|";
            ksiazkaAdresowa << kontakty[i].imie << "|";
            ksiazkaAdresowa << kontakty[i].nazwisko <<"|";
            ksiazkaAdresowa << kontakty[i].numerTel << "|";
            ksiazkaAdresowa << kontakty[i].eMail << "|";
            ksiazkaAdresowa << kontakty[i].adresZamieszkania << "|" << endl;
        }
    }
    ksiazkaAdresowa.close();
}

void edytujImie (vector<Kontakt>& kontakty) {

    int idKontaktu;
    string noweImie = "";

    cout << "Podaj id kontaktu do edycji imienia: ";
    idKontaktu = wczytajLiczbeCalkowita();

    while(true) {
        if (idKontaktu > kontakty.back().id) {
            cout << "Id kontaktu spoza zakresu dostepnej liczby kontaktow. Podaj poprawne id: ";
            idKontaktu = wczytajLiczbeCalkowita();
        } else {
            for (int i = 0; i < kontakty.size(); i++) {

                if (kontakty[i].id == idKontaktu) {
                    cout << "Podaj nowe imie: ";
                    noweImie = wczytajLinie();
                    kontakty[i].imie = noweImie;
                }
            }
            uaktualnijKsiazkeAdresowaPoEdycji(kontakty);
            break;
        }
    }
}

void edytujNazwisko (vector<Kontakt>& kontakty) {

    int idKontaktu;
    string noweNazwisko = "";

    cout << "Podaj id kontaktu do edycji nazwiska: ";
    idKontaktu = wczytajLiczbeCalkowita();

    while (true) {
        if (idKontaktu > kontakty.back().id) {
            cout << "Id kontaktu spoza zakresu dostepnej liczby kontaktow. Podaj poprawne id: ";
            idKontaktu = wczytajLiczbeCalkowita();
        } else {
            for (int i = 0; i < kontakty.size(); i++) {

                if (kontakty[i].id == idKontaktu) {

                    cout << "Podaj nowe nazwisko: ";
                    noweNazwisko = wczytajLinie();
                    kontakty[i].nazwisko = noweNazwisko;
                }
            }
            uaktualnijKsiazkeAdresowaPoEdycji(kontakty);
            break;
        }
    }
}

void edytujNumerTel (vector<Kontakt>& kontakty) {

    int idKontaktu;
    string nowyNumerTel = "";

    cout << "Podaj id kontaktu do edycji numeru telefonu: ";
    idKontaktu = wczytajLiczbeCalkowita();

    while(true) {
        if (idKontaktu > kontakty.back().id) {
            cout << "Id kontaktu spoza zakresu dostepnej liczby kontaktow. Podaj poprawne id: ";
            idKontaktu = wczytajLiczbeCalkowita();
        } else {
            for (int i = 0; i < kontakty.size(); i++) {

                if (kontakty[i].id == idKontaktu) {

                    cout << "Podaj nowy numer telefonu: ";
                    nowyNumerTel = wczytajLinie();
                    kontakty[i].numerTel = nowyNumerTel;
                }
            }
            uaktualnijKsiazkeAdresowaPoEdycji(kontakty);
            break;
        }
    }
}

void edytujEMail (vector<Kontakt>& kontakty) {

    int idKontaktu;
    string nowyEMail = "";

    cout << "Podaj id kontaktu do edycji adresu e-mail: ";
    idKontaktu = wczytajLiczbeCalkowita();

    while (true) {
        if (idKontaktu > kontakty.back().id) {
            cout << "Id kontaktu spoza zakresu dostepnej liczby kontaktow. Podaj poprawne id: ";
            idKontaktu = wczytajLiczbeCalkowita();
        } else {
            for (int i = 0; i < kontakty.size(); i++) {

                if (kontakty[i].id == idKontaktu) {

                    cout << "Podaj nowy adres e-mail: ";
                    cin >> nowyEMail;
                    kontakty[i].eMail = nowyEMail;
                }
            }
            uaktualnijKsiazkeAdresowaPoEdycji(kontakty);
            break;
        }
    }
}

void edytujAdresZamieszkania (vector<Kontakt>& kontakty) {

    int idKontaktu;
    string nowyAdresZamieszkania = "";

    cout << "Podaj id kontaktu do edycji adresu zamieszkania: ";
    idKontaktu = wczytajLiczbeCalkowita();

    while(true) {
        if (idKontaktu > kontakty.back().id) {
            cout << "Id kontaktu spoza zakresu dostepnej liczby kontaktow. Podaj poprawne id: ";
            idKontaktu = wczytajLiczbeCalkowita();
        } else {
            for (int i = 0; i < kontakty.size(); i++) {

                if (kontakty[i].id == idKontaktu) {

                    cout << "Podaj nowy adres zamieszkania: ";
                    nowyAdresZamieszkania = wczytajLinie();
                    kontakty[i].adresZamieszkania = nowyAdresZamieszkania;
                }
            }
            uaktualnijKsiazkeAdresowaPoEdycji(kontakty);
            break;
        }
    }
}

void usunKontakt(vector<Kontakt>& kontakty, int &liczbaKontaktow) {

    int idKontaktu;
    vector <Kontakt>::iterator it;

    cout << "Podaj id kontaktu, ktory chcesz skasowac: ";
    idKontaktu = wczytajLiczbeCalkowita();

    while(true) {
        if (idKontaktu > kontakty.back().id) {
            cout << "Id kontaktu spoza zakresu dostepnej liczby kontaktow. Podaj poprawne id: ";
            idKontaktu = wczytajLiczbeCalkowita();
        } else {
            cout << "Czy napewno chcesz skasowac kontakt? Zatwierdz operacje wciskajac 't' na klawiaturze... : ";
            if (wczytajZnak() == 't') {
                for (int i = 0; i < kontakty.size(); i++) {

                    if (kontakty[i].id == idKontaktu) {
                        it = kontakty.begin() + i;
                        kontakty.erase(it);
                        liczbaKontaktow = kontakty.size();
                    }
                }
                uaktualnijKsiazkeAdresowaPoEdycji(kontakty);
                cout << "Kontakt zostal skasowany!";
                Sleep(1500);
                break;
            } else {
                cout << "Nie wyrazono zgody na usuniecie kontaktu z ksiazki adresowej!";
                Sleep(2000);
                break;
            }
        }
    }
}

void wyswietlMenu (vector<Kontakt>& kontakty, int liczbaKontaktow) {
    char wybor;

    while (1) {
Menu_glowne:
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
        cout << "Ksiazka adresowa" << endl;
        cout << "Liczba kontaktow: " << liczbaKontaktow << endl << endl;
        cout << "Menu glowne:" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        cout << "-------------------------------------------------------------------------" << endl;
        cout << "1. Dodaj kontakt do ksiazki adresowej." << endl;
        cout << "2. Wyszukaj kontakt w ksiazce adresowej." << endl;
        cout << "3. Wyswietl liste wszystkich kontaktow w ksiazce adresowej." << endl;
        cout << "4. Edytuj kontakt." << endl;
        cout << "5. Usun kontakt." << endl;
        cout << "9. Zamknij ksiazke adresowa." << endl;
        cout << "-------------------------------------------------------------------------" << endl;
        cin >> wybor;

        switch(wybor) {
        case '1':
            liczbaKontaktow = dodajKontakt (kontakty, liczbaKontaktow);
            break;

        case '2':
Menu_wyszukiwania_kontaktow:
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
            cout << "Menu wyszukiwania kontaktow:" << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            cout << "----------------------------------------------------" << endl;
            cout << "1. Wyszukaj kontakt  po imieniu." << endl;
            cout << "2. Wyszukaj kontakt  po nazwisku." << endl;
            cout << "3. Powrot do menu glownego." << endl;
            cout << "----------------------------------------------------" << endl;
            cin >> wybor;

            switch(wybor) {
            case '1':
                if (liczbaKontaktow == 0) {
                    cout << "Lista kontaktow w ksiazce adresowej jest pusta. Dodaj najpierw kontakty do ksiazki adresowej aby je wyswietlic!" << endl;
                    Sleep (2500);
                    goto Menu_glowne;
                } else {
                    system("cls");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    cout << "Wyszukaj kontakt po imieniu: " << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                    cout << "------------------------------------------------" << endl;
                    wyszukajKontaktPoImieniu (kontakty);
                    goto Menu_wyszukiwania_kontaktow;
                }
                break;

            case '2':
                if (liczbaKontaktow == 0) {
                    cout << "Lista kontaktow w ksiazce adresowej jest pusta. Dodaj najpierw kontakty do ksiazki adresowej aby je wyswietlic!" << endl;
                    Sleep (2500);
                    goto Menu_glowne;
                } else {
                    system("cls");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    cout << "Wyszukaj kontakt po nazwisku: " << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                    cout << "------------------------------------------------" << endl;
                    wyszukajKontaktPoNazwisku (kontakty);
                    goto Menu_wyszukiwania_kontaktow;
                }
                break;

            case '3':
                goto Menu_glowne;
                break;
            }
            break;

        case '3':
            if (liczbaKontaktow == 0) {
                cout << "Lista kontaktow w ksiazce adresowej jest pusta. Dodaj najpierw kontakty do ksiazki adresowej aby je wyswietlic!" << endl;
                Sleep (2500);
            } else {
                system("cls");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                cout << "Lista wszystkich kontaktow w ksiazce adresowej: " << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                cout << "----------------------------------------------------------" << endl;
                wyswietlListeWszystkichKontaktow (kontakty);
            }
            break;

        case '4':
            if (liczbaKontaktow == 0) {
                system("cls");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                cout << "Menu edycji kontaktow:" << endl;
                cout << "----------------------------------------------------" << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                cout << "Brak danych do edycji. Lista kontaktow jest pusta!" << endl;
                Sleep (2500);
                goto Menu_glowne;
            } else {
                system("cls");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                cout << "Menu edycji kontaktow:" << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                cout << "----------------------------------------------------" << endl;
                cout << "1. Edytuj imie." << endl;
                cout << "2. Edytuj nazwisko." << endl;
                cout << "3. Edytuj numer telefonu." << endl;
                cout << "4. Edytuj e-mial." << endl;
                cout << "5. Edytuj adres zamieszkania." << endl;
                cout << "6. Powrot do menu glownego." << endl;
                cout << "----------------------------------------------------" << endl;
                cin >> wybor;

                switch(wybor) {
                case '1':
                    system("cls");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    cout << "Edytuj imie:" << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                    cout << "----------------------------------------------------" << endl;
                    edytujImie(kontakty);
                    goto Menu_glowne;
                    break;
                case '2':
                    system("cls");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    cout << "Edytuj nazwisko:" << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                    cout << "----------------------------------------------------" << endl;
                    edytujNazwisko(kontakty);
                    goto Menu_glowne;
                    break;
                case '3':
                    system("cls");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    cout << "Edytuj nazwisko:" << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                    cout << "----------------------------------------------------" << endl;
                    edytujNumerTel(kontakty);
                    goto Menu_glowne;
                    break;
                case '4':
                    system("cls");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    cout << "Edytuj nazwisko:" << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                    cout << "----------------------------------------------------" << endl;
                    edytujEMail(kontakty);
                    goto Menu_glowne;
                    break;
                case '5':
                    system("cls");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    cout << "Edytuj nazwisko:" << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                    cout << "----------------------------------------------------" << endl;
                    edytujAdresZamieszkania(kontakty);
                    goto Menu_glowne;
                    break;
                case '6':
                    goto Menu_glowne;
                    break;
                }
            }

        case '5':
            if (liczbaKontaktow == 0) {
                system("cls");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                cout << "Usuwanie kontaktow z ksiazki adresowej:" << endl;
                cout << "----------------------------------------------------" << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                cout << "Ksiazka adresowa jest pusta, nie ma co usuwac!" << endl;
                Sleep (2500);
                goto Menu_glowne;
            } else {
                system("cls");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                cout << "Usuwanie kontakow z ksiazki adresowej:" << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                cout << "----------------------------------------------------" << endl;
                usunKontakt(kontakty, liczbaKontaktow);
                break;
            }

        case '9':
            exit(0);
            break;
        }
    }
}

int main() {
    vector<Kontakt> kontakty;
    Kontakt daneKontaktowe;
    int liczbaKontaktow = 0;

    wczytajKsiazkeAdresowa (kontakty);
    liczbaKontaktow = kontakty.size();
    wyswietlMenu (kontakty, liczbaKontaktow);

    return 0;
}
