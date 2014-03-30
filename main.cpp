#include <iostream>
#include <string>

using namespace std;

class cZahtjev{
private:
    bool dok_ok;
    string ime;
    string prezime;
    string adresa;
public:
    cZahtjev(string ime, string prez, string adr, bool dok){
        this->ime=ime;
        this->prezime=prez;
        this->adresa=adr;
        this->dok_ok=dok;
    }
    string get_zahtjev(){
        return (ime+" "+prezime+", "+adresa+". "+(dok_ok ? "Dokumentacija OK.":"Nedostaje dokumentacija."));
    }

};

class cLista{
    cZahtjev * zahtjev;
    cLista * next;
    string sluzbenik;
public:
    void DodajNoviZahtjev(string ime, string prez, string adr, bool dok){
        cLista * tmp1 = new cLista;
        tmp1->zahtjev =  new cZahtjev(ime, prez, adr, dok);
        tmp1->next = NULL;
        cLista * tmp2 = new cLista;
        tmp2 = this;
        if(this->zahtjev == NULL)
            this->zahtjev = tmp1->zahtjev;
        else
        {

            while(tmp2->next != NULL ){
                tmp2=tmp2->next;
            }
            tmp2->next = tmp1;
        }
    }
    ~cLista(){
        delete(zahtjev);
        delete(next);
    }
};

int main()
{
    cLista * lista = new cLista;

    lista->DodajNoviZahtjev("hbjkhb", "7trfzubj", "bla", true);
    lista->DodajNoviZahtjev("34sgs553", "53255dsfgf", "bla", true);
    lista->DodajNoviZahtjev("1324", "214dwqwd", "bl64a", true);
    lista->DodajNoviZahtjev("67568", "arweatr", "6wqbla", true);
    lista->DodajNoviZahtjev("1324we64", "afawr", "rqw", true);
    lista->DodajNoviZahtjev("1w534q324", "fas", "dfgsabla", true);
    cout << "Hello World!" << endl;
    return 0;
}

