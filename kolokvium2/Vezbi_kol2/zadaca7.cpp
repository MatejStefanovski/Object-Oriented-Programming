#include<iostream>
#include<string.h>
using namespace std;

class Karticka{
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
public:
    Karticka() {
        pin = 0;
        povekjePin = false;
        strcpy(smetka, "0123456789");
    }
    Karticka(char* smetka,int pin){
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePin=false;
    }
    Karticka(const Karticka& k) {
        strcpy(smetka,k.smetka);
        this->pin=k.pin;
        this->povekjePin=k.povekjePin;
    }
    int tezina_prob() {
        int t=0, k=pin;
        while (k!=0) {
            k/=10;
            t++;
        }
        return t;
    }
};

class SpecijalnaKarticka:public Karticka{
private:
    int *niza;
    int br;
public:
    SpecijalnaKarticka():Karticka() {
        this->niza=new int[1];
        br=0;
    }
    SpecijalnaKarticka(char *smetka, int pin):Karticka(smetka, pin) {
        this->niza=new int[1];
        this->povekjePin=false;
        this->br=0;
    }
    

};

class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else this->karticki[i]=new Karticka(*karticki[i]);
        }
        this->broj=broj;
    }
    ~Banka(){
        for (int i=0;i<broj;i++) delete karticki[i];
    }

    //да се дополни класата

};



int main(){

    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else
            niza[i]=new SpecijalnaKarticka(smetka,pin);
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>smetka>>pin;

        komercijalna.dodadiDopolnitelenPin(smetka,pin);

    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}
