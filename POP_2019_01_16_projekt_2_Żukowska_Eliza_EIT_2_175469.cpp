//POP_2019_01_16_projekt_2_¯ukowska_Eliza_EIT_2_175469
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


void wypiszDanePliku ( int liczbaZnakowWwierszu, int liczbaWierszy, char txt[])
{
    for(int w=0; w<liczbaWierszy; w++)
    {
        int poczatek = w*liczbaZnakowWwierszu;
        int koniec = poczatek + liczbaZnakowWwierszu;
        for(int i=poczatek; i<koniec; i++)
        {
            cout << setfill('0') << setw(2) << hex << static_cast<int>(txt[i]) << " ";
        }
        cout << "| ";
        for(int i=poczatek; i<koniec; i++)
        {
            if(txt[i]=='\n' || txt[i]=='\r' || txt[i]=='\t' || txt[i]=='\b' || txt[i]=='\a')
                cout << '.';
            else
                cout << txt[i];
        }
        cout << " |" << endl;
    }
}
int main()
{
    string nazwaPliku;
    cout<<"Podaj nazwe pliku: ";
    cin>>nazwaPliku;

    fstream plik(nazwaPliku.c_str(), ios::in | ios::binary | ios::out);
    if(!plik)
    {
        cout << "Plik nie zostal otwarty";
        return 1;
    }
    int liczbaZnakowWBuforze;
    int liczbaWierszyZPliku;
    int liczbaZnakowWwierszu;

    cout << "Podaj ile wierszy wczytac znakow z pliku: ";
    cin >> liczbaWierszyZPliku;

    cout << "Podaj ile znakow w wierszu: ";
    cin >> liczbaZnakowWwierszu;

    liczbaZnakowWBuforze = liczbaWierszyZPliku * liczbaZnakowWwierszu;

    char dane[liczbaZnakowWBuforze];

    plik.read(dane, liczbaZnakowWBuforze);
    cout<<"Wczytano "<<plik.gcount()<<" bajtow do bufora"<<endl;

    plik.seekg(0, ios::end);
    int dlugoscPliku = plik.tellg();
    cout <<"ilosc bajtow w pliku: " << dec << dlugoscPliku << endl ;

    wypiszDanePliku(liczbaZnakowWwierszu, liczbaWierszyZPliku, dane);
    plik.seekg(0, ios::beg);
    
    cout<< "Wcisnij:"<<endl;
    cout<<"'1' aby przejsc na poczatek pliku"<<endl;
    cout<<"'2' aby przejsc na koniec pliku"<<endl;
    cout<<"'3' aby przesunac odczyt pliku w prawo"<<endl;
    cout<<"'4' aby przesunac odczyt pliku w lewo"<<endl;
    cout<<"'5' aby przejsc na dowolna pozycje odczytu"<<endl;
    cout<<"'6' aby edytowac pierwszy bajt w wypisanej czesci pliku"<<endl;
    cout<<"'0' aby zakonczyc program"<<endl;

    while(plik)
    {

        int przesuniecie;
        streampos pozycja = plik.tellg();
        cout << "Pozycja kursora w pliku: '" << dec << pozycja << "'" << endl;
        int przycisk;
        cin >> przycisk;
        switch(przycisk)
        {
        case 1:
            cout << "Przejscie na poczatek pliku" << endl;
            plik.seekg(0, ios::beg);
            plik.read(dane, liczbaZnakowWBuforze);
            wypiszDanePliku(liczbaZnakowWwierszu, liczbaWierszyZPliku, dane);

            plik.seekg(0, ios::beg);
            break;
        case 2:
            cout << "Przejscie na koniec pliku" << endl;
            plik.seekg(-liczbaZnakowWBuforze, ios::end);
            if( plik.tellg() > dlugoscPliku )
            {
                cout << "Error! Nie udalo sie przesunac wewnetrznego wskaznika pliku" << endl;
                break;
            }
            else
            {
                plik.read(dane, liczbaZnakowWBuforze);
                wypiszDanePliku(liczbaZnakowWwierszu, liczbaWierszyZPliku, dane);
                plik.seekg(-liczbaZnakowWBuforze, ios::end);
                break;
            }
        case 3:
            cout << "O ile chcesz przesunac wskaznik odczytu pliku w prawo: ";
            cin >> przesuniecie;
            plik.seekg(przesuniecie, ios::cur);
            if(plik.tellg() > dlugoscPliku - liczbaZnakowWBuforze)
            {
                cout << "Error! Nie udalo sie przesunac wewnetrznego wskaznika pliku" << endl;
                break;
            }
            else
            {
                plik.read(dane, liczbaZnakowWBuforze);
                wypiszDanePliku(liczbaZnakowWwierszu, liczbaWierszyZPliku, dane);
                plik.seekg(-liczbaZnakowWBuforze, ios::cur);
                break;
            }
        case 4:
            cout << "O ile chcesz przesunac wskaznik odczytu pliku w lewo: ";
            cin >> przesuniecie;
            plik.seekg(-przesuniecie, ios::cur);
            if(plik.tellg() < 0)
            {
                cout << "Error! Nie udalo sie przesunac wewnetrznego wskaznika pliku" << endl;
                break;
            }
            else
            {
                plik.read(dane, liczbaZnakowWBuforze);
                wypiszDanePliku(liczbaZnakowWwierszu, liczbaWierszyZPliku, dane);
                plik.seekg(-liczbaZnakowWBuforze, ios::cur);
                break;
            }
        case 5:
            cout << "Podaj pozycje wskaznika na ktora chcesz sie przeniesc:";
            cin >> przesuniecie;
            plik.seekg(przesuniecie,ios::beg);
            if(plik.tellg() > dlugoscPliku)
            {
                cout << "Error! Nie udalo sie przesunac wewnetrznego wskaznika pliku" << endl;
                break;
            }
            else
            {
                plik.read(dane, liczbaZnakowWBuforze);
                wypiszDanePliku(liczbaZnakowWwierszu, liczbaWierszyZPliku, dane);
                plik.seekg(-liczbaZnakowWBuforze, ios::cur);
                break;
            }
        case 6:
            cout << "Zamiana bajtu na danej pozycji"<<endl;
            char edycjaA;
            int edycja;
            char system;
            cout << "W jakim systemie podajesz bajt? [d = dec / h = hex / a = ASCII] ";
            cin >> system;
            if (system == 'd') //wpisanie danych w systemie dziesiêtnym
            {
                cin >> dec >> edycja;
                plik<< (char)edycja;
            }
            else if (system == 'h') //wpisanie danych w systemie heksadecymalnym
            {
                cin >> hex >> edycja;
                plik << (char)edycja;
            }
            else if (system == 'a') //wpisanie danych korzystajac z ASCII
            {
                cin >> edycjaA;
                plik << edycjaA;
            }
            else
            {
                cout << "Blad!" << endl;
                break;
            }
            plik.flush();
            plik.seekg(-1, ios::cur);
            plik.read(dane, liczbaZnakowWBuforze);
            wypiszDanePliku(liczbaZnakowWwierszu, liczbaWierszyZPliku, dane);
            plik.seekg(-liczbaZnakowWBuforze, ios::cur);
            break;

        case 0:
            plik.close();
            return 0;

        default:
            cout << "Nie ten przycisk" << endl;
            break;
        }

    }


    plik.close();
    return 0;
}
