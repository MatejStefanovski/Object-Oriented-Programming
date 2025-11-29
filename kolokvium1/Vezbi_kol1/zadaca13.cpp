#include<iostream>
#include<cstring>

using namespace std;

class Zichara {
private:
    char *mesto;
    int cena;
public:
    Zichara() {
        this->mesto = new char[1];
        strcpy(this->mesto, "");
        this->cena = 0;
    }
    Zichara(char *mesto, int cena) {
        this->mesto = new char[strlen(mesto)+1];
        strcpy(this->mesto, mesto);
        this->cena = cena;
    }
    ~Zichara() {
        delete [] this->mesto;
    }
};

class PlaninarskiDom {
private:
    char ime[15];
    int cena_sezona[2];
    char klasa;
    bool ima_zichara;
    Zichara *zichara;
public:
    PlaninarskiDom() {
        strcpy(ime, "");
        cena_sezona[0] = 0;
        cena_sezona[1] = 0;
        ima_zichara = false;
        zichara = new Zichara[0];
    }
    PlaninarskiDom(char *ime, int cena_sezona[], char klasa, bool ima_zichara, Zichara *zichara) {

    }
    ~PlaninarskiDom() {
        delete [] zichara;
    }

};

int main(){

    PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

    //во следниот дел се вчитуваат информации за планинарскиот дом
    char imePlaninarskiDom[15],mestoZichara[30],klasa;
    int ceni[12];
    int dnevnakartaZichara;
    bool daliZichara;
    cin>>imePlaninarskiDom;
    for (int i=0;i<2;i++) cin>>ceni[i];
    cin>>klasa;
    cin>>daliZichara;

    //во следниот дел се внесуваат информации и за жичарата ако постои
    if (daliZichara) {
        cin>>mestoZichara>>dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom,ceni,klasa);
        Zichara r(mestoZichara,dnevnakartaZichara);
        pom.setZichara(r);
        p=pom;
    }
    else{
        PlaninarskiDom *pok=new PlaninarskiDom(imePlaninarskiDom,ceni,klasa);
        p=*pok;
    }

    //се намалува класата на планинарскиот дом за 2
    --p;
    --p;

    int cena;
    int den,mesec;
    cin>>den>>mesec;
    try{
        p.presmetajDnevenPrestoj(den,mesec,cena); //тука се користи функцијата presmetajDnevenPrestoj
        cout<<"Informacii za PlaninarskiDomot:"<<endl;
        cout<<p;
        if (p<='D')
            cout<<"Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";

        cout<<"Cenata za "<<den<<"."<<mesec<<" e "<<cena; //се печати цената за дадениот ден и месец
    }
    catch (int){
        cout<<"Mesecot ili denot e greshno vnesen!";
    }
}
