
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <map>

using namespace std;

class Artikel;
class verkaufteArtikel;
class Warengruppe;


class Artikel{
public:
    Artikel(int artnr, const string &name);
    void verkaufen(int betrag, int amount);
    int artnr;
    string name;
    list<verkaufteArtikel> verkaufteArt;
};

class verkaufteArtikel{
public:
    verkaufteArtikel(int artnr, const string &datum, double betrag, double summe);
    int artnr;
    string datum;
    double betrag;
    double summe;
};

class Warengruppe{
public:
    Warengruppe(int wgrne, const string &name, const list<Artikel> &warengruppe);

    int wgrne;
    string name;
    list<Artikel> warengruppe;
};

void lesedatei()
{
    FILE *fp;
    int i=0, artnr;
    float preis;
    char name[100];
    int anzEinrage = 0;

    fp=fopen("d:\\artikel.txt", "r+");
    if (fp==NULL)
        return;
    fseek(fp, 0, SEEK_SET);

    while(!feof(fp))
    {
        anzEinrage++;
    }
    fseek(fp, 0, SEEK_SET);
    typedef struct {
        int artnr;
        float preis;
        char name[100];
    } TY_Artikel;
    TY_Artikel a[anzEinrage];

    while(!feof(fp))
    {
        fscanf(fp, "%d;%f;%s\n", &(a[i].artnr), &(a[i].preis), a[i].name);
        i++;
    }
    fclose(fp);
};
    //map <int,int> mapAnzahl;

Artikel::Artikel(int artnr, const string &name) : artnr(artnr), name(name){}

void Artikel::verkaufen(int betrag, int amount) {
    this->verkaufteArt.insert(this->verkaufteArt.end(),verkaufteArtikel(this->artnr, "Heute", (double) betrag, (double) betrag*amount));
}

verkaufteArtikel::verkaufteArtikel(int artnr, const string &datum, double betrag, double summe) : artnr(artnr),
                                                                                                  datum(datum),
                                                                                                  betrag(betrag),
                                                                                                  summe(summe) {}

Warengruppe::Warengruppe(int wgrne, const string &name, const list<Artikel> &warengruppe) : wgrne(wgrne), name(name),warengruppe(warengruppe) {}

void meistverkauft(list<Artikel> Sortiment){
        int max = 0;
        list<Artikel>::iterator maximum;
        for(auto a = Sortiment.begin(); a != Sortiment.end(); a++){
            int summe =0;
            for(auto b = a->verkaufteArt.begin(); b != a->verkaufteArt.end(); b++){
                summe+=b->summe;
            }
            if(summe>max){
                max = summe;
                maximum = a;
            }
        }
        cout << "Maximum ist " << maximum->name << " mit artikel nummer " << maximum->artnr << endl;

};

int main() {
    list<Artikel> Sortiment= {Artikel(12,"Gay"),Artikel(24,"ÄÖÄÜ")};
    list<Artikel>::iterator Stelle= Sortiment.begin();
    Stelle->verkaufen(12,4);
    Stelle++;
    Stelle->verkaufen(10,7);

    meistverkauft(Sortiment);
    return 0;
}