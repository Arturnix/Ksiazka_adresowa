#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Uzytkownik {
    int id = 0;
    string nazwa, haslo;
};

struct Kontakt {
    int id = 0, idUzytkownika = 0;
    string imie = "", nazwisko = "", numerTel = "", eMail = "", adresZamieszkania = "";
};

string wczytajLinie () {
    string wejscie = "";
    cin.sync();
    getline(cin, wejscie);

    return wejscie;
}

void wczytajListeUzytkownikow (vector<Uzytkownik>& uzytkownicy) {

    Uzytkownik daneUzytkownika;
    string liniaZListyUzytkownikow, daneUzytkownikaStr;
    fstream listaUzytkownikow;

    listaUzytkownikow.open("Lista_uzytkownikow.txt", ios::in);
    if(listaUzytkownikow.good()==true) {
        while(!listaUzytkownikow.eof()) {

            getline (listaUzytkownikow, liniaZListyUzytkownikow);

            if (liniaZListyUzytkownikow.find('|') != string::npos) {
                size_t separatorDanychWPliku = liniaZListyUzytkownikow.find('|');

                daneUzytkownikaStr = liniaZListyUzytkownikow.substr(0, separatorDanychWPliku);
                daneUzytkownika.id = atoi(daneUzytkownikaStr.c_str());
                liniaZListyUzytkownikow = liniaZListyUzytkownikow.erase(0, separatorDanychWPliku+1);

                separatorDanychWPliku = liniaZListyUzytkownikow.find('|');
                daneUzytkownika.nazwa = liniaZListyUzytkownikow.substr(0, separatorDanychWPliku);
                liniaZListyUzytkownikow = liniaZListyUzytkownikow.erase(0, separatorDanychWPliku+1);

                separatorDanychWPliku = liniaZListyUzytkownikow.find('|');
                daneUzytkownika.haslo = liniaZListyUzytkownikow.substr(0, separatorDanychWPliku);
                liniaZListyUzytkownikow = liniaZListyUzytkownikow.erase(0, separatorDanychWPliku+1);

                uzytkownicy.push_back(daneUzytkownika);
            }
        }
    }
    listaUzytkownikow.close();
}

void dodajKontaktDoPliku (Uzytkownik daneUzytkownika) {

    fstream listaUzytkownikow;
    listaUzytkownikow.open("Lista_uzytkownikow.txt", ios::out | ios::app);
    if(listaUzytkownikow.good()==true) {
        listaUzytkownikow << daneUzytkownika.id << "|";
        listaUzytkownikow << daneUzytkownika.nazwa << "|";
        listaUzytkownikow << daneUzytkownika.haslo << endl;
    }
    listaUzytkownikow.close();
}

void uaktualnijListeKontaktow (vector<Uzytkownik>& uzytkownicy) {

    fstream listaUzytkownikow;
    listaUzytkownikow.open("Lista_uzytkownikow.txt", ios::out);
    if(listaUzytkownikow.good()==true) {
        for (int i = 0; i < (int) uzytkownicy.size(); i++) {

            listaUzytkownikow << uzytkownicy[i].id << "|";
            listaUzytkownikow << uzytkownicy[i].nazwa << "|";
            listaUzytkownikow << uzytkownicy[i].haslo << endl;
        }
    }
    listaUzytkownikow.close();
}

int rejestracja (vector<Uzytkownik>& uzytkownicy, int iloscUzytkownikow) {
    Uzytkownik daneUzytkownika;
    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    daneUzytkownika.nazwa = wczytajLinie();

    int i = 0;
    while (i < iloscUzytkownikow) {
        if (uzytkownicy[i].nazwa == nazwa) {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            daneUzytkownika.nazwa = wczytajLinie();
            i = 0;
        } else {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    daneUzytkownika.haslo = wczytajLinie();

    iloscUzytkownikow++;
    if (uzytkownicy.size() == 0) {
        daneUzytkownika.id = iloscUzytkownikow;
    } else {
        daneUzytkownika.id = uzytkownicy.back().id + 1;
    }
    daneUzytkownika.id = iloscUzytkownikow;
    uzytkownicy.push_back(daneUzytkownika);
    dodajKontaktDoPliku(daneUzytkownika);

    cout << "Konto zalozone." << endl;
    Sleep(1000);
    return iloscUzytkownikow;
}

int logowanie (vector<Uzytkownik>& uzytkownicy, int iloscUzytkownikow) {
    string nazwa, haslo;

    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;

    int i = 0;
    while (i < iloscUzytkownikow) {
        if (uzytkownicy[i].nazwa == nazwa) {
            for (int proby = 0; proby < 3; proby++) {
                cout << "Podaj haslo. Pozostalo prob " << 3 - proby << ": ";
                cin >> haslo;
                if (uzytkownicy[i].haslo == haslo) {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }
            }
            cout << "Podales bledne haslo. Zaczekaj 3 sekundy przed kolejna proba." << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika z takim loginem." << endl;
    Sleep(1500);
    return 0;
}

void zmianaHasla (vector<Uzytkownik>& uzytkownicy, Uzytkownik daneUzytkownika, int iloscUzytkownikow, int idZalogowanegoUzytkownika) {
    string noweHaslo = "";
    cout << "Podaj nowe haslo: ";
    noweHaslo = wczytajLinie();

    for (int i = 0; i < iloscUzytkownikow; i++) {
        if (uzytkownicy[i].id == idZalogowanegoUzytkownika) {
            uzytkownicy[i].haslo = noweHaslo;
        }
    }
    uaktualnijListeKontaktow(uzytkownicy);
    cout << "Haslo zostalo zmienione." << endl;
    Sleep(1500);
}

void wyswietlMenuLogowania(int iloscUzytkownikow) {

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << "Ksiazka adresowa - menu logowania" << endl;
    cout << "Liczba zarejestrowanych uzytkownikow: " << iloscUzytkownikow << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "1. Rejsetracja" << endl;
    cout << "2. Logowanie" << endl;
    cout << "3. Zamknij program" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
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

void wczytajKsiazkeAdresowa (vector<Kontakt>& kontakty, vector<Kontakt>& kontaktyZalogowanegoUzytkownika, int idZalogowanegoUzytkownika) {
    Kontakt daneKontaktowe;
    string liniaZKsiazkiAdresowej = "", daneKontaktoweStr = "";
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

                if (daneKontaktoweStr.length() == 1) {  //dla kazdego rzedu wielkosci. Inaczej ucina litery z przodu imienia zgodnie z rzedem wielkosci x10.
                    daneKontaktoweStr = liniaZKsiazkiAdresowej.substr(0, separatorDanychWPliku);
                    daneKontaktowe.idUzytkownika = atoi(daneKontaktoweStr.c_str());
                    liniaZKsiazkiAdresowej = liniaZKsiazkiAdresowej.erase(0, separatorDanychWPliku+1);

                    separatorDanychWPliku = liniaZKsiazkiAdresowej.find('|');
                    daneKontaktowe.imie = liniaZKsiazkiAdresowej.substr(0, separatorDanychWPliku);
                    liniaZKsiazkiAdresowej = liniaZKsiazkiAdresowej.erase(0, separatorDanychWPliku+1);
                }
                if (daneKontaktoweStr.length() == 2) {
                    daneKontaktoweStr = liniaZKsiazkiAdresowej.substr(0, separatorDanychWPliku);
                    daneKontaktowe.idUzytkownika = atoi(daneKontaktoweStr.c_str());
                    liniaZKsiazkiAdresowej = liniaZKsiazkiAdresowej.erase(0, separatorDanychWPliku);

                    separatorDanychWPliku = liniaZKsiazkiAdresowej.find('|');
                    daneKontaktowe.imie = liniaZKsiazkiAdresowej.substr(0, separatorDanychWPliku);
                    liniaZKsiazkiAdresowej = liniaZKsiazkiAdresowej.erase(0, separatorDanychWPliku+1);
                }

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

                if (daneKontaktowe.idUzytkownika == idZalogowanegoUzytkownika) {
                    kontaktyZalogowanegoUzytkownika.push_back(daneKontaktowe);
                }
            }
        }
    }
    ksiazkaAdresowa.close();
}

void dodajKontaktDoPliku (Kontakt daneKontaktowe) {
    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("Ksiazka_Adresowa.txt", ios::out | ios::app | ios::ate);
    if(ksiazkaAdresowa.good()==true) {
        ksiazkaAdresowa << daneKontaktowe.id << "|";
        ksiazkaAdresowa << daneKontaktowe.idUzytkownika << "|";
        ksiazkaAdresowa << daneKontaktowe.imie << "|";
        ksiazkaAdresowa << daneKontaktowe.nazwisko <<"|";
        ksiazkaAdresowa << daneKontaktowe.numerTel << "|";
        ksiazkaAdresowa << daneKontaktowe.eMail << "|";
        ksiazkaAdresowa << daneKontaktowe.adresZamieszkania << "|" << endl;
    }
    ksiazkaAdresowa.close();
}

int dodajKontakt (vector<Kontakt>& kontakty, vector<Kontakt>& kontaktyZalogowanegoUzytkownika, int liczbaKontaktow, int idZalogowanegoUzytkownika) {
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
    daneKontaktowe.idUzytkownika = idZalogowanegoUzytkownika;

    liczbaKontaktow++;

    if (kontaktyZalogowanegoUzytkownika.size() == 0){
        daneKontaktowe.id = liczbaKontaktow;
    } else {
        daneKontaktowe.id = kontakty.back().id + 1;
    }

    kontaktyZalogowanegoUzytkownika.push_back(daneKontaktowe);
    kontakty.push_back(daneKontaktowe);
    dodajKontaktDoPliku (daneKontaktowe);

    cout << "Dodano kontakt do ksiazki adresowej." << endl;
    Sleep(1000);
    return liczbaKontaktow;
}

void wyszukajKontaktPoImieniu (vector<Kontakt>& kontaktyZalogowanegoUzytkownika) {
    string imie;
    int nieZnalezionoImienia = 0;

    cout << "Podaj imie do wyszukania kontaktu: ";
    imie = wczytajLinie();

    for (int i = 0; i < (int) kontaktyZalogowanegoUzytkownika.size(); i++) {
        if (kontaktyZalogowanegoUzytkownika[i].imie == imie) {
            cout << "\nId kontaktu: " << kontaktyZalogowanegoUzytkownika[i].id << endl;
            cout << "Imie: " << kontaktyZalogowanegoUzytkownika[i].imie << endl;
            cout << "Nazwisko: "<< kontaktyZalogowanegoUzytkownika[i].nazwisko << endl;
            cout << "Nr telefonu: " << kontaktyZalogowanegoUzytkownika[i].numerTel << endl;
            cout << "E-mail: " << kontaktyZalogowanegoUzytkownika[i].eMail << endl;
            cout << "Adres zamieszkania: " << kontaktyZalogowanegoUzytkownika[i].adresZamieszkania << endl;
        } else {
            nieZnalezionoImienia++;
            if (nieZnalezionoImienia == (int) kontaktyZalogowanegoUzytkownika.size()) {
                cout << "Brak takiego kontaktu do wyswietlenia!" << endl;
            }
        }
    }
    system ("pause");
}

void wyszukajKontaktPoNazwisku (vector<Kontakt>& kontaktyZalogowanegoUzytkownika) {
    string nazwisko;
    int nieZnalezionoNazwiska = 0;

    cout << "Podaj nazwisko do wyszukania kontaktu: ";
    nazwisko = wczytajLinie();

    for (int i = 0; i < (int) kontaktyZalogowanegoUzytkownika.size(); i++) {
        if (kontaktyZalogowanegoUzytkownika[i].nazwisko == nazwisko) {
            cout << '\n' << "Id kontaktu: " << kontaktyZalogowanegoUzytkownika[i].id << endl;
            cout << "Nazwisko: " << kontaktyZalogowanegoUzytkownika[i].nazwisko << endl;
            cout << "Imie: " << kontaktyZalogowanegoUzytkownika[i].imie << endl;
            cout << "Nr telefonu: " << kontaktyZalogowanegoUzytkownika[i].numerTel << endl;
            cout << "E-mail: " << kontaktyZalogowanegoUzytkownika[i].eMail << endl;
            cout << "Adres zamieszkania: " << kontaktyZalogowanegoUzytkownika[i].adresZamieszkania << endl;
        } else {
            nieZnalezionoNazwiska++;
            if (nieZnalezionoNazwiska == (int) kontaktyZalogowanegoUzytkownika.size()) {
                cout << "Brak takiego kontaktu do wyswietlenia!" << endl;
            }
        }
    }
    system ("pause");
}

void wyswietlListeWszystkichKontaktow (vector<Kontakt>& kontaktyZalogowanegoUzytkownika) {

    for (int i = 0; i < (int) kontaktyZalogowanegoUzytkownika.size(); i++) {
        cout << "\nId kontaktu: " << kontaktyZalogowanegoUzytkownika[i].id << endl;
        cout << "Imie: " << kontaktyZalogowanegoUzytkownika[i].imie << endl;
        cout << "Nazwisko: "<< kontaktyZalogowanegoUzytkownika[i].nazwisko << endl;
        cout << "Nr telefonu: " << kontaktyZalogowanegoUzytkownika[i].numerTel << endl;
        cout << "E-mail: " << kontaktyZalogowanegoUzytkownika[i].eMail << endl;
        cout << "Adres zamieszkania: " << kontaktyZalogowanegoUzytkownika[i].adresZamieszkania << endl;
    }
    system ("pause");
}

//Korzystalem z tej funkcji ale dodaje puste wiersze w pliku wiec sprobowalem zrobic to na wektorze w funkcji ponizej o tej samej nazwie.
/*void uaktualnijKsiazkeAdresowaPoEdycji (vector<Kontakt>& kontakty, vector<Kontakt>& kontaktyZalogowanegoUzytkownika, int idKontaktu) {

    fstream ksiazkaAdresowa;
    fstream ksiazkaAdresowaTymczasowa;
    string liniaZKsiazkiAdresowej = "", daneKontaktoweStr = "";
    int idZKsiazki = 0;

    ksiazkaAdresowa.open("Ksiazka_Adresowa.txt", ios::in);
    ksiazkaAdresowaTymczasowa.open("Ksiazka_adresowa_tymczasowa.txt", ios::out | ios::ate);
    if(ksiazkaAdresowa.good() == true && ksiazkaAdresowaTymczasowa.good() == true) {
        while(!ksiazkaAdresowa.eof()) {

            getline (ksiazkaAdresowa, liniaZKsiazkiAdresowej);
            if (liniaZKsiazkiAdresowej.find('|') != string::npos) {
                size_t separatorDanychWPliku = liniaZKsiazkiAdresowej.find('|');

                daneKontaktoweStr = liniaZKsiazkiAdresowej.substr(0, separatorDanychWPliku);
                idZKsiazki = atoi(daneKontaktoweStr.c_str());
            }
            if (idZKsiazki != idKontaktu) {
                ksiazkaAdresowaTymczasowa << liniaZKsiazkiAdresowej << endl;
            } else {
                for (int i = 0; i < (int) kontakty.size(); i++) {
                    if (kontaktyZalogowanegoUzytkownika[i].id == idKontaktu) {
                        ksiazkaAdresowaTymczasowa << kontaktyZalogowanegoUzytkownika[i].id << "|";
                        ksiazkaAdresowaTymczasowa << kontaktyZalogowanegoUzytkownika[i].idUzytkownika << "|";
                        ksiazkaAdresowaTymczasowa << kontaktyZalogowanegoUzytkownika[i].imie << "|";
                        ksiazkaAdresowaTymczasowa << kontaktyZalogowanegoUzytkownika[i].nazwisko <<"|";
                        ksiazkaAdresowaTymczasowa << kontaktyZalogowanegoUzytkownika[i].numerTel << "|";
                        ksiazkaAdresowaTymczasowa << kontaktyZalogowanegoUzytkownika[i].eMail << "|";
                        ksiazkaAdresowaTymczasowa << kontaktyZalogowanegoUzytkownika[i].adresZamieszkania << "|" << endl;
                    }
                }
            }
        }
    }
    ksiazkaAdresowa.close();
    ksiazkaAdresowaTymczasowa.close();
    remove("Ksiazka_Adresowa.txt");
    rename("Ksiazka_adresowa_tymczasowa.txt", "Ksiazka_Adresowa.txt");
}*/

void uaktualnijKsiazkeAdresowaPoEdycji (vector<Kontakt>& kontakty, vector<Kontakt>& kontaktyZalogowanegoUzytkownika, int idKontaktu) {

    fstream ksiazkaAdresowa;
    fstream ksiazkaAdresowaTymczasowa;
    string liniaZKsiazkiAdresowej = "", daneKontaktoweStr = "";

    ksiazkaAdresowaTymczasowa.open("Ksiazka_adresowa_tymczasowa.txt", ios::out | ios::ate);
    if(ksiazkaAdresowaTymczasowa.good() == true) {

        for (int i = 0; i < (int) kontakty.size(); i++) {
            ksiazkaAdresowaTymczasowa << kontakty[i].id << "|";
            ksiazkaAdresowaTymczasowa << kontakty[i].idUzytkownika << "|";
            ksiazkaAdresowaTymczasowa << kontakty[i].imie << "|";
            ksiazkaAdresowaTymczasowa << kontakty[i].nazwisko <<"|";
            ksiazkaAdresowaTymczasowa << kontakty[i].numerTel << "|";
            ksiazkaAdresowaTymczasowa << kontakty[i].eMail << "|";
            ksiazkaAdresowaTymczasowa << kontakty[i].adresZamieszkania << "|" << endl;
        }
    }
    ksiazkaAdresowaTymczasowa.close();
    remove("Ksiazka_Adresowa.txt");
    rename("Ksiazka_adresowa_tymczasowa.txt", "Ksiazka_Adresowa.txt");
}

void uaktualnijKsiazkeAdresowaPoUsunieciu (vector<Kontakt>& kontakty, vector<Kontakt>& kontaktyZalogowanegoUzytkownika, int idKontaktu) {

    fstream ksiazkaAdresowa;
    fstream ksiazkaAdresowaTymczasowa;
    string liniaZKsiazkiAdresowej = "", daneKontaktoweStr = "";
    int idZKsiazki = 0;

    ksiazkaAdresowa.open("Ksiazka_Adresowa.txt", ios::in);
    ksiazkaAdresowaTymczasowa.open("Ksiazka_adresowa_tymczasowa.txt", ios::out | ios::ate);
    if(ksiazkaAdresowa.good() == true) {
        for (int i = 0; i < (int) kontakty.size(); i++) {

            getline (ksiazkaAdresowa, liniaZKsiazkiAdresowej);
            if (liniaZKsiazkiAdresowej.find('|') != string::npos) {
                size_t separatorDanychWPliku = liniaZKsiazkiAdresowej.find('|');

                daneKontaktoweStr = liniaZKsiazkiAdresowej.substr(0, separatorDanychWPliku);
                idZKsiazki = atoi(daneKontaktoweStr.c_str());
            }
            if (idZKsiazki != idKontaktu) {
                ksiazkaAdresowaTymczasowa << liniaZKsiazkiAdresowej << endl;
            }
        }
    }
    ksiazkaAdresowaTymczasowa.close();
    ksiazkaAdresowa.close();
    remove("Ksiazka_Adresowa.txt");
    rename("Ksiazka_adresowa_tymczasowa.txt", "Ksiazka_Adresowa.txt");
}

void edytujImie (vector<Kontakt>& kontaktyZalogowanegoUzytkownika, vector<Kontakt>& kontakty) {

    int idKontaktu;
    string noweImie = "";

    cout << "Podaj id kontaktu do edycji imienia: ";
    idKontaktu = wczytajLiczbeCalkowita();

    while(true) {
        if (idKontaktu > kontaktyZalogowanegoUzytkownika.back().id) {
            cout << "Id kontaktu spoza zakresu dostepnej liczby kontaktow. Podaj poprawne id: ";
            idKontaktu = wczytajLiczbeCalkowita();
        } else {
            for (int i = 0; i < (int) kontaktyZalogowanegoUzytkownika.size(); i++) {

                if (kontaktyZalogowanegoUzytkownika[i].id == idKontaktu) {
                    cout << "Podaj nowe imie: ";
                    noweImie = wczytajLinie();
                    kontaktyZalogowanegoUzytkownika[i].imie = noweImie;
                    kontakty[i].imie = noweImie;
                }
            }
            uaktualnijKsiazkeAdresowaPoEdycji(kontakty, kontaktyZalogowanegoUzytkownika, idKontaktu);
            break;
        }
    }
}

void edytujNazwisko (vector<Kontakt>& kontaktyZalogowanegoUzytkownika, vector<Kontakt>& kontakty) {

    int idKontaktu;
    string noweNazwisko = "";

    cout << "Podaj id kontaktu do edycji nazwiska: ";
    idKontaktu = wczytajLiczbeCalkowita();

    while (true) {
        if (idKontaktu > kontaktyZalogowanegoUzytkownika.back().id) {
            cout << "Id kontaktu spoza zakresu dostepnej liczby kontaktow. Podaj poprawne id: ";
            idKontaktu = wczytajLiczbeCalkowita();
        } else {
            for (int i = 0; i < (int) kontaktyZalogowanegoUzytkownika.size(); i++) {

                if (kontaktyZalogowanegoUzytkownika[i].id == idKontaktu) {

                    cout << "Podaj nowe nazwisko: ";
                    noweNazwisko = wczytajLinie();
                    kontaktyZalogowanegoUzytkownika[i].nazwisko = noweNazwisko;
                }
            }
            uaktualnijKsiazkeAdresowaPoEdycji(kontakty, kontaktyZalogowanegoUzytkownika, idKontaktu);
            break;
        }
    }
}

void edytujNumerTel (vector<Kontakt>& kontaktyZalogowanegoUzytkownika, vector<Kontakt>& kontakty) {

    int idKontaktu;
    string nowyNumerTel = "";

    cout << "Podaj id kontaktu do edycji numeru telefonu: ";
    idKontaktu = wczytajLiczbeCalkowita();

    while(true) {
        if (idKontaktu > kontaktyZalogowanegoUzytkownika.back().id) {
            cout << "Id kontaktu spoza zakresu dostepnej liczby kontaktow. Podaj poprawne id: ";
            idKontaktu = wczytajLiczbeCalkowita();
        } else {
            for (int i = 0; i < (int) kontaktyZalogowanegoUzytkownika.size(); i++) {

                if (kontaktyZalogowanegoUzytkownika[i].id == idKontaktu) {

                    cout << "Podaj nowy numer telefonu: ";
                    nowyNumerTel = wczytajLinie();
                    kontaktyZalogowanegoUzytkownika[i].numerTel = nowyNumerTel;
                }
            }
            uaktualnijKsiazkeAdresowaPoEdycji(kontakty, kontaktyZalogowanegoUzytkownika, idKontaktu);
            break;
        }
    }
}

void edytujEMail (vector<Kontakt>& kontaktyZalogowanegoUzytkownika, vector<Kontakt>& kontakty) {

    int idKontaktu;
    string nowyEMail = "";

    cout << "Podaj id kontaktu do edycji adresu e-mail: ";
    idKontaktu = wczytajLiczbeCalkowita();

    while (true) {
        if (idKontaktu > kontaktyZalogowanegoUzytkownika.back().id) {
            cout << "Id kontaktu spoza zakresu dostepnej liczby kontaktow. Podaj poprawne id: ";
            idKontaktu = wczytajLiczbeCalkowita();
        } else {
            for (int i = 0; i < (int) kontaktyZalogowanegoUzytkownika.size(); i++) {

                if (kontaktyZalogowanegoUzytkownika[i].id == idKontaktu) {

                    cout << "Podaj nowy adres e-mail: ";
                    cin >> nowyEMail;
                    kontaktyZalogowanegoUzytkownika[i].eMail = nowyEMail;
                }
            }
            uaktualnijKsiazkeAdresowaPoEdycji(kontakty, kontaktyZalogowanegoUzytkownika, idKontaktu);
            break;
        }
    }
}

void edytujAdresZamieszkania (vector<Kontakt>& kontaktyZalogowanegoUzytkownika, vector<Kontakt>& kontakty) {

    int idKontaktu;
    string nowyAdresZamieszkania = "";

    cout << "Podaj id kontaktu do edycji adresu zamieszkania: ";
    idKontaktu = wczytajLiczbeCalkowita();

    while(true) {
        if (idKontaktu > kontaktyZalogowanegoUzytkownika.back().id) {
            cout << "Id kontaktu spoza zakresu dostepnej liczby kontaktow. Podaj poprawne id: ";
            idKontaktu = wczytajLiczbeCalkowita();
        } else {
            for (int i = 0; i < (int) kontaktyZalogowanegoUzytkownika.size(); i++) {

                if (kontaktyZalogowanegoUzytkownika[i].id == idKontaktu) {

                    cout << "Podaj nowy adres zamieszkania: ";
                    nowyAdresZamieszkania = wczytajLinie();
                    kontaktyZalogowanegoUzytkownika[i].adresZamieszkania = nowyAdresZamieszkania;
                }
            }
            uaktualnijKsiazkeAdresowaPoEdycji(kontakty, kontaktyZalogowanegoUzytkownika, idKontaktu);
            break;
        }
    }
}

void usunKontakt(vector<Kontakt>& kontakty, vector<Kontakt>& kontaktyZalogowanegoUzytkownika, int &liczbaKontaktow) {

    int idKontaktu;
    vector <Kontakt>::iterator it;

    cout << "Podaj id kontaktu, ktory chcesz skasowac: ";
    idKontaktu = wczytajLiczbeCalkowita();

    while(true) {
        if (idKontaktu > kontaktyZalogowanegoUzytkownika.back().id) {
            cout << "Id kontaktu spoza zakresu dostepnej liczby kontaktow. Podaj poprawne id: ";
            idKontaktu = wczytajLiczbeCalkowita();
        } else {
            cout << "Czy napewno chcesz skasowac kontakt? Zatwierdz operacje wciskajac 't' na klawiaturze... : ";
            if (wczytajZnak() == 't') {
                for (int i = 0; i < (int) kontaktyZalogowanegoUzytkownika.size(); i++) {

                    if (kontaktyZalogowanegoUzytkownika[i].id == idKontaktu) {
                        it = kontaktyZalogowanegoUzytkownika.begin() + i;
                        kontaktyZalogowanegoUzytkownika.erase(it);
                        liczbaKontaktow = kontaktyZalogowanegoUzytkownika.size();
                    }
                }
                uaktualnijKsiazkeAdresowaPoUsunieciu(kontakty, kontaktyZalogowanegoUzytkownika, idKontaktu);
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

void wyswietlManuKsiazkiAdresowej (int idZalogowanegoUzytkownika, vector<Kontakt>& kontaktyZalogowanegoUzytkownika) {

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << "Ksiazka adresowa" << endl;
    cout << "Id zalogowanego uzytkownia: " << idZalogowanegoUzytkownika << endl;
    cout << "Liczba kontaktow: " << kontaktyZalogowanegoUzytkownika.size() << endl << endl;
    cout << "Menu glowne:" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "1. Dodaj kontakt do ksiazki adresowej." << endl;
    cout << "2. Wyszukaj kontakt w ksiazce adresowej." << endl;
    cout << "3. Wyswietl liste wszystkich kontaktow w ksiazce adresowej." << endl;
    cout << "4. Edytuj kontakt." << endl;
    cout << "5. Usun kontakt." << endl;
    cout << "6. Zmien haslo." << endl;
    cout << "7. Wyloguj sie." << endl;
    cout << "8. Zamknij ksiazke adresowa." << endl;
    cout << "-------------------------------------------------------------------------" << endl;
}

void wyswietlManuWyszukiwaniaKontaktow () {

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << "Menu wyszukiwania kontaktow:" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout << "----------------------------------------------------" << endl;
    cout << "1. Wyszukaj kontakt  po imieniu." << endl;
    cout << "2. Wyszukaj kontakt  po nazwisku." << endl;
    cout << "3. Powrot do menu glownego." << endl;
    cout << "----------------------------------------------------" << endl;
}

void wyswietlWyszukaniePoImieniu () {

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << "Wyszukaj kontakt po imieniu: " << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout << "------------------------------------------------" << endl;
}

void wyswietlWyszukaniePoNazwisku () {

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << "Wyszukaj kontakt po nazwisku: " << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout << "------------------------------------------------" << endl;
}

void wyswietlNaglowekListyWszystkichKontaktow () {

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << "Lista wszystkich kontaktow w ksiazce adresowej: " << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout << "----------------------------------------------------------" << endl;
}

void wyswietlBrakDanychDoEdycji () {

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << "Menu edycji kontaktow:" << endl;
    cout << "----------------------------------------------------" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout << "Brak danych do edycji. Lista kontaktow jest pusta!" << endl;
    Sleep (2500);
}

void wyswietlMenuEdycjiKontaktow () {

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
}

void wyswietlNaglowekEdytujImie () {

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << "Edytuj imie:" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout << "----------------------------------------------------" << endl;
}

void wyswietlNaglowekEdytujNazwisko () {

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << "Edytuj nazwisko:" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout << "----------------------------------------------------" << endl;
}

void wyswietlNaglowekEdytujNrTel () {

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << "Edytuj numer telefonu:" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout << "----------------------------------------------------" << endl;
}

void wyswietlNaglowekEdytujEmail () {

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << "Edytuj email:" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout << "----------------------------------------------------" << endl;
}

void wyswietlNaglowekEdytujAdresZamieszkania () {

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << "Edytuj adres zamieszkania:" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout << "----------------------------------------------------" << endl;
}

void wyswietlNaglowekUsuwaniaKsiazkaPusta () {

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << "Usuwanie kontaktow z ksiazki adresowej:" << endl;
    cout << "----------------------------------------------------" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout << "Ksiazka adresowa jest pusta, nie ma co usuwac!" << endl;
    Sleep (2500);
}

void wyswietlNaglowekUsuwaniaKontaktu () {

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << "Usuwanie kontakow z ksiazki adresowej:" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout << "----------------------------------------------------" << endl;
}

void wyswietlMenuGlowne (vector<Kontakt>& kontakty, vector<Kontakt>& kontaktyZalogowanegoUzytkownika, int liczbaKontaktow, int idZalogowanegoUzytkownika, int iloscUzytkownikow, vector<Uzytkownik>& uzytkownicy, Uzytkownik daneUzytkownika) {

    char wybor;

    while (1) {
Menu_logowania:
        if (idZalogowanegoUzytkownika == 0) {

            wyswietlMenuLogowania (iloscUzytkownikow);
            cin >> wybor;

            if (wybor == '1') {
                iloscUzytkownikow = rejestracja (uzytkownicy, iloscUzytkownikow);
            }

            else if (wybor == '2') {
                idZalogowanegoUzytkownika = logowanie (uzytkownicy, iloscUzytkownikow);
            }

            else if (wybor == '3') {
                exit(0);
            }
        }

        else {

            goto Menu_glowne;

        }
    }

    while (1) {
Menu_glowne:

        kontakty.erase(kontakty.begin(), kontakty.end());
        kontaktyZalogowanegoUzytkownika.erase(kontaktyZalogowanegoUzytkownika.begin(), kontaktyZalogowanegoUzytkownika.end());
        wczytajKsiazkeAdresowa (kontakty, kontaktyZalogowanegoUzytkownika, idZalogowanegoUzytkownika);
        wyswietlManuKsiazkiAdresowej (idZalogowanegoUzytkownika, kontaktyZalogowanegoUzytkownika);

        cin >> wybor;

        switch(wybor) {
        case '1':
            liczbaKontaktow = dodajKontakt (kontakty, kontaktyZalogowanegoUzytkownika, liczbaKontaktow, idZalogowanegoUzytkownika);
            break;

        case '2':
Menu_wyszukiwania_kontaktow:

            wyswietlManuWyszukiwaniaKontaktow ();
            cin >> wybor;

            switch(wybor) {
            case '1':
                if (kontaktyZalogowanegoUzytkownika.size() == 0) {
                    cout << "Lista kontaktow w ksiazce adresowej jest pusta. Dodaj najpierw kontakty do ksiazki adresowej aby je wyswietlic!" << endl;
                    Sleep (2500);
                    goto Menu_glowne;
                } else {
                    wyswietlWyszukaniePoImieniu ();
                    wyszukajKontaktPoImieniu (kontaktyZalogowanegoUzytkownika);
                    goto Menu_wyszukiwania_kontaktow;
                }
                break;

            case '2':
                if (kontaktyZalogowanegoUzytkownika.size() == 0) {
                    cout << "Lista kontaktow w ksiazce adresowej jest pusta. Dodaj najpierw kontakty do ksiazki adresowej aby je wyswietlic!" << endl;
                    Sleep (2500);
                    goto Menu_glowne;
                } else {
                    wyswietlWyszukaniePoNazwisku();
                    wyszukajKontaktPoNazwisku (kontaktyZalogowanegoUzytkownika);
                    goto Menu_wyszukiwania_kontaktow;
                }
                break;

            case '3':
                goto Menu_glowne;
                break;
            }
            break;

        case '3':
            if (kontaktyZalogowanegoUzytkownika.size() == 0) {
                cout << "Lista kontaktow w ksiazce adresowej jest pusta. Dodaj najpierw kontakty do ksiazki adresowej aby je wyswietlic!" << endl;
                Sleep (2500);
            } else {
                wyswietlNaglowekListyWszystkichKontaktow ();
                wyswietlListeWszystkichKontaktow (kontaktyZalogowanegoUzytkownika);
            }
            break;

        case '4':
            if (kontaktyZalogowanegoUzytkownika.size() == 0) {
                wyswietlBrakDanychDoEdycji ();
                goto Menu_glowne;
            } else {
                wyswietlMenuEdycjiKontaktow ();
                cin >> wybor;

                switch(wybor) {
                case '1':
                    wyswietlNaglowekEdytujImie ();
                    edytujImie(kontaktyZalogowanegoUzytkownika, kontakty);
                    goto Menu_glowne;
                    break;
                case '2':
                    wyswietlNaglowekEdytujNazwisko ();
                    edytujNazwisko(kontaktyZalogowanegoUzytkownika, kontakty);
                    goto Menu_glowne;
                    break;
                case '3':
                    wyswietlNaglowekEdytujNrTel ();
                    edytujNumerTel(kontaktyZalogowanegoUzytkownika, kontakty);
                    goto Menu_glowne;
                    break;
                case '4':
                    wyswietlNaglowekEdytujEmail ();
                    edytujEMail(kontaktyZalogowanegoUzytkownika, kontakty);
                    goto Menu_glowne;
                    break;
                case '5':
                    wyswietlNaglowekEdytujAdresZamieszkania ();
                    edytujAdresZamieszkania(kontaktyZalogowanegoUzytkownika, kontakty);
                    goto Menu_glowne;
                    break;
                case '6':
                    goto Menu_glowne;
                    break;
                }
            }

        case '5':
            if (kontaktyZalogowanegoUzytkownika.size() == 0) {
                wyswietlNaglowekUsuwaniaKsiazkaPusta ();
                goto Menu_glowne;
            } else {
                wyswietlNaglowekUsuwaniaKontaktu ();
                usunKontakt(kontakty, kontaktyZalogowanegoUzytkownika, liczbaKontaktow);
                break;
            }

        case '6':
            zmianaHasla(uzytkownicy, daneUzytkownika, iloscUzytkownikow, idZalogowanegoUzytkownika);
            goto Menu_glowne;

        case '7':
            idZalogowanegoUzytkownika = 0;
            goto Menu_logowania;

        case '8':
            exit(0);
            break;
        }
    }
}

int main() {

    vector<Uzytkownik> uzytkownicy;
    Uzytkownik daneUzytkownika;
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = 0;
    vector<Kontakt> kontakty;
    vector<Kontakt> kontaktyZalogowanegoUzytkownika;
    Kontakt daneKontaktowe;
    int liczbaKontaktow = 0;

    wczytajListeUzytkownikow (uzytkownicy);
    iloscUzytkownikow = uzytkownicy.size();
    wyswietlMenuGlowne (kontakty, kontaktyZalogowanegoUzytkownika, liczbaKontaktow, idZalogowanegoUzytkownika, iloscUzytkownikow, uzytkownicy, daneUzytkownika);

    return 0;
}
