#include <iostream>
#include <string>
#define BR_SLUZ 5
//#define TEST
#define ZAHTJEVI

using namespace std;

class cZahtjev{
private:
    bool geo;
    bool arh;
    bool stat;
    bool dok_ok;
    string ime;
    string prezime;
    string adresa;
    int sluzbenik;
public:
    cZahtjev(){};
    cZahtjev(string ime, string prez, string adr, bool geo, bool arh, bool stat){
        this->ime=ime;
        this->prezime=prez;
        this->adresa=adr;
        this->geo=geo;
        this->arh=arh;
        this->stat=stat;
    }
    string get_zahtjev(){
        if(this != NULL) return (ime+" "+prezime+", "+adresa+". "+(dok_ok ? "Dokumentacija OK.":"Nedostaje dokumentacija."));
        else return "nema zahtjeva";
    }
    bool get_dokumentacija(){
        return ((geo && arh && stat) ? true : false);
    }
    bool set_dok_ok(int sluz){
        if(geo && arh && stat){
            this->sluzbenik = sluz;
            return this->dok_ok=true;
        }
        else return false;
    }
};

class cSluzbenik{
    int sluzbenik;
public:
    void set_sluz(int sluz){
        this->sluzbenik = sluz;
    }
    int get_sluz(){
        return this->sluzbenik;
    }

    bool ObradaZahtjeva(cZahtjev * zahtjev){
        return zahtjev->set_dok_ok(sluzbenik);
    }
};

class cLista{
    cZahtjev * zahtjev;
    cLista * next;
    cLista * tail;
    //cLista * head; // this->head = this->next;
public:
    void SpremiZahtjev(cZahtjev * zahtjev){
        cLista * tmp1 = new cLista;
        tmp1->zahtjev =  zahtjev;
        tmp1->next = NULL;
        tmp1->tail = NULL;
        if (this->next == NULL)
            this->next = tmp1;
        else
            this->tail->next = tmp1;

        this->tail = tmp1;
    }

    cZahtjev * DohvatiZahtjev(){
        if(this->next == NULL) return NULL;
        else {
            cLista * first = this->next;
            cZahtjev * tmp = first->zahtjev;
            this->next = this->next->next;
            first->zahtjev = NULL;
            first->next = NULL;
            first->tail = NULL;
            delete first;
            first = NULL;
            return tmp;
        }
    }

    void IspisSvihZathjeva(){
        if(this->next != NULL){
            cLista * tmp=this->next;
            while(1){
                cout << tmp->zahtjev->get_zahtjev() << endl;
                if(tmp->next != NULL)
                    tmp = tmp->next;
                else
                    break;
            }
        }
    }

    cLista(){
        this->next = NULL;
        this->tail = NULL;
        // this->head = this->next;
    }

    ~cLista(){
        cLista * tmp = new cLista;
        while(1){
            tmp = this->next;
            if (tmp != NULL)
            {
                delete tmp->zahtjev;
                if (this->next->next != NULL)
                {
                    this->next->zahtjev = this->next->next->zahtjev;
                    this->next = this->next->next;
                }
                else
                    break;
                tmp->next = NULL;
            }
            else
                break;
        }
        delete tmp;
    }
};

int main()
{
    cZahtjev * zahtjev;
    cLista * neobradeni = new cLista;
    cLista * obradeni = new cLista;
    cSluzbenik sluzbenik[BR_SLUZ];
    for(int i=0; i<BR_SLUZ ; i++)
        sluzbenik[i].set_sluz(i+1);

#ifndef TEST
#ifdef ZAHTJEVI
    zahtjev = new cZahtjev("hbjkhb", "7trfzubj", "bla", true, true, true);
    neobradeni->SpremiZahtjev(zahtjev);
    zahtjev = new cZahtjev("34sgs553", "53255dsfgf", "bla", true, true, true );
    neobradeni->SpremiZahtjev(zahtjev);
    zahtjev = new cZahtjev("1324", "214dwqwd", "bl64a", true, true, true);
    neobradeni->SpremiZahtjev(zahtjev);
    zahtjev = new cZahtjev("67568", "arweatr", "6wqbla", true, false, true);
    neobradeni->SpremiZahtjev(zahtjev);
    zahtjev = new cZahtjev("1324we64", "afawr", "rqw", true, true, true);
    neobradeni->SpremiZahtjev(zahtjev);
    zahtjev = new cZahtjev("1w534q324", "fas", "dfgsabla", false, true, true);
    neobradeni->SpremiZahtjev(zahtjev);
#endif

    int i;
    string str;
    while(1){
        cout << string( 100, '\n' );
        cout << "1 - Novi zahtjev" << endl;
        cout << "2 - Obradi zahtjev" << endl;
        cout << "3 - Ispiši riješene predmete" << endl;
        cout << "Bilo koji drugi broj za prekid" << endl;
        cin >> str;
        if(str == "1"){
            string ime, prez, adr;
            bool geo, arh, stat;
            cout << string( 100, '\n' );
            cout << "Podaci o podnositelju zahtjeva" << endl;
            cout << "      Ime: ";
            cin >> ime;
            cout << "  Prezime: ";
            cin >> prez;
            cout << "   Adresa: ";
            cin >> adr;
            cout << "Dokumentacija (0 ako postoji ili 1 ako ne postoji)" << endl;
            cout << "       Geodetska podloga: ";
            cin >> geo;
            cout << "  Arhitektonski elaborat: ";
            cin >> arh;
            cout << "       Statički proračun: ";
            cin >> stat;
            zahtjev = new cZahtjev(ime, prez, adr, geo, arh, stat);
            neobradeni->SpremiZahtjev(zahtjev);
            cout << "Zahtjev spremljen.";
            cin.get();
            cin.get();
        }
        else if(str == "2"){
            cout << string( 100, '\n' );
            cout << "Upiši broj službenika (1 do " << BR_SLUZ << "): ";
            cin >> i;
            if ((zahtjev = neobradeni->DohvatiZahtjev()) != NULL){
                if(sluzbenik[i-1].ObradaZahtjeva(zahtjev)){
                    obradeni->SpremiZahtjev(zahtjev);
                    cout << "Dokumentacija potpuna. Zahtjev obrađen." << endl;
                    cin.get();
                    cin.get();
                }
                else {
                    neobradeni->SpremiZahtjev(zahtjev);
                    cout << "Dokumentacija nepotpuna. Zahtjev nije obrađen." << endl;
                    cin.get();
                    cin.get();
                }
            }
            else {
                cout << "Nema neobrađenih zahtjeva." << endl;
                cin.get();
                cin.get();
            }
        }
        else if(str == "3"){
            cout << string( 100, '\n' );
            obradeni->IspisSvihZathjeva();
            cin.get();
            cin.get();
        }
        else break;
    }
#else
    zahtjev = new cZahtjev("hbjkhb", "7trfzubj", "bla", true, true, true);
    neobradeni->SpremiZahtjev(zahtjev);
    zahtjev = new cZahtjev("34sgs553", "53255dsfgf", "bla", true, true, true );
    neobradeni->SpremiZahtjev(zahtjev);
    zahtjev = new cZahtjev("1324", "214dwqwd", "bl64a", true, true, true);
    neobradeni->SpremiZahtjev(zahtjev);
    zahtjev = new cZahtjev("67568", "arweatr", "6wqbla", true, false, true);
    neobradeni->SpremiZahtjev(zahtjev);
    zahtjev = new cZahtjev("1324we64", "afawr", "rqw", true, true, true);
    neobradeni->SpremiZahtjev(zahtjev);
    zahtjev = new cZahtjev("1w534q324", "fas", "dfgsabla", false, true, true);
    neobradeni->SpremiZahtjev(zahtjev);
    cLista * temp = new cLista;
    do
    {
        zahtjev = neobradeni->DohvatiZahtjev();
//        cout << zahtjev->get_zahtjev() << endl;
        if(sluzbenik[1].ObradaZahtjeva(zahtjev))
        {
            cout << "Obrađen:   " << zahtjev->get_zahtjev() << endl;
            obradeni->SpremiZahtjev(zahtjev);

        }
        else
        {
            cout << "Neobrađen: "<< zahtjev->get_zahtjev() << endl;
            temp->SpremiZahtjev(zahtjev);

        }
      //  cout << zahtjev->get_zahtjev() << endl;
    } while (zahtjev->get_zahtjev() != "nema zahtjeva");
    neobradeni = temp;
    delete temp;
    /*
    zahtjev = neobradeni->DohvatiZahtjev();
    cout << zahtjev->get_zahtjev() << endl;
    zahtjev = neobradeni->DohvatiZahtjev();
    cout << zahtjev->get_zahtjev() << endl;
    zahtjev = neobradeni->DohvatiZahtjev();
    cout << zahtjev->get_zahtjev() << endl;
    zahtjev = neobradeni->DohvatiZahtjev();
    cout << zahtjev->get_zahtjev() << endl;
    zahtjev = neobradeni->DohvatiZahtjev();
    cout << zahtjev->get_zahtjev() << endl;
    zahtjev = neobradeni->DohvatiZahtjev();
    cout << zahtjev->get_zahtjev() << endl;
*/
#endif

    delete neobradeni;
    neobradeni = NULL;
    delete obradeni;
    obradeni = NULL;
    delete zahtjev;
    zahtjev = NULL;
    return 0;
}

