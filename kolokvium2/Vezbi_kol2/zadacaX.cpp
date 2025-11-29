#include <iostream>   //ZADACA 10
#include <cstring>

using namespace std;

class NegativnaVrednost {
public:
    NegativnaVrednost() {
        cout << "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!" << endl;
    }
};

class Oglas {
private:
    char naslov[51];
    char kategorija[31];
    char opis[101];
    float cena;

public:
    Oglas() {
        strcpy(naslov, "");
        strcpy(kategorija, "");
        strcpy(opis, "");
        cena = 0;
    }

    Oglas(const char *naslov, const char *kategorija, const char *opis, float cena) {
        strncpy(this->naslov, naslov, 50);
        this->naslov[50] = '\0';
        strncpy(this->kategorija, kategorija, 30);
        this->kategorija[30] = '\0';
        strncpy(this->opis, opis, 100);
        this->opis[100] = '\0';
        this->cena = cena;
    }

    float getCena() const {
        return cena;
    }

    const char* getOpis() const {
        return opis;
    }

    const char* getNaslov() const {
        return naslov;
    }

    const char* getKategorija() const {
        return kategorija;
    }

    friend bool operator>(const Oglas &o1, const Oglas &o2) {
        return o1.cena > o2.cena;
    }

    friend ostream& operator<<(ostream &out, const Oglas &o) {
        out << o.naslov << endl;
        out << o.opis << endl;
        out << o.cena << " evra" << endl;
        return out;
    }
};

class Oglasnik {
private:
    char ime[21];
    Oglas *oglasi;
    int broj;

public:
    Oglasnik(const char *ime) {
        strncpy(this->ime, ime, 20);
        this->ime[20] = '\0';
        this->broj = 0;
        this->oglasi = nullptr;
    }

    ~Oglasnik() {
        delete[] oglasi;
    }

    Oglasnik& operator+=(const Oglas &o) {
        if (o.getCena() < 0) {
            throw NegativnaVrednost();
        }

        Oglas *temp = new Oglas[broj + 1];
        for (int i = 0; i < broj; i++) {
            temp[i] = oglasi[i];
        }
        temp[broj] = o;
        delete[] oglasi;
        oglasi = temp;
        broj++;
        return *this;
    }

    friend ostream& operator<<(ostream &out, const Oglasnik &o) {
        out << o.ime << endl;
        for (int i = 0; i < o.broj; i++) {
            out << o.oglasi[i].getNaslov() << endl
                << o.oglasi[i].getOpis() << endl
                << o.oglasi[i].getCena() << " evra" << endl << endl;
        }
        return out;
    }

    void oglasiOdKategorija(const char *k) const {
        for (int i = 0; i < broj; i++) {
            if (strcmp(oglasi[i].getKategorija(), k) == 0) {
                cout << oglasi[i];
                cout << endl;
            }
        }
    }

    void najniskaCena() const {
        if (broj == 0) return;
        int minIndex = 0;
        for (int i = 1; i < broj; i++) {
            if (oglasi[i].getCena() < oglasi[minIndex].getCena()) {
                minIndex = i;
            }
        }
        cout << oglasi[minIndex];
    }
};

int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
    	cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;
    }
    else if (tip==4){
      	cout<<"-----Test oglasOdKategorija -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
    	cout<<"-----Test Exception -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            try {
                cin.get();
                cin.getline(naslov,49);
                cin.getline(kategorija,29);
                cin.getline(opis,99);
                cin>>cena;
                Oglas o(naslov, kategorija, opis, cena);
                ogl+=o;
            }
            catch (NegativnaVrednost& e){}
        }
        cout<<ogl;

    }
    else if (tip==6){
    	cout<<"-----Test najniskaCena -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }
    else if (tip==7){
    	cout<<"-----Test All -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            try {
                cin.get();
                cin.getline(naslov,49);
                cin.getline(kategorija,29);
                cin.getline(opis,99);
                cin>>cena;
                Oglas o(naslov, kategorija, opis, cena);
                ogl+=o;
            }
            catch (NegativnaVrednost& e) {}
        }
        cout<<ogl;

        cin.get();
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }

	return 0;
}


// /*#include <iostream> //ZADACA 5
// #include <cstring>
// #define MAX 50
//
// using namespace std;
//
// class UserExistsException {
// public:
//   void print() {
//     cout << "The user already exists in the list" << endl;
//   }
// };
//
// enum typeC {
//   standard=0, loyal, vip
// };
//
// class Customer {
// private:
//   char ime[50];
//   char e_adresa[50];
//   typeC vid;
//   int br_proizvodi;
// public:
//   static double osnoven_popust;
//   static double dopolnitelen_popust;
//   Customer() {
//     strcpy(ime,"");
//     strcpy(e_adresa,"");
//     vid=standard;
//     br_proizvodi=0;
//   }
//   Customer(char *ime, char *e_adresa, typeC vid, int br_proizvodi) {
//     strcpy(this->ime, ime);
//     strcpy(this->e_adresa, e_adresa);
//     this->vid=vid;
//     this->br_proizvodi=br_proizvodi;
//   }
//   Customer(const Customer &c) {
//     strcpy(this->ime, c.ime);
//     strcpy(this->e_adresa, c.e_adresa);
//     this->vid=c.vid;
//     this->br_proizvodi=c.br_proizvodi;
//   }
//   static void setDiscount1(float f) {
//     osnoven_popust=f;
//   }
//   friend ostream& operator<<(ostream &out, Customer &c) {
//     out << c.ime << endl << c.e_adresa << endl << c.br_proizvodi << endl;
//     if (c.vid==standard) {
//       cout << "standard" << " " << 0 << endl;
//     }
//     else if (c.vid==loyal) {
//       cout << "loyal" << " " << osnoven_popust << endl;
//     }
//     else if (c.vid==vip) {
//       cout << "vip" << " " << osnoven_popust+dopolnitelen_popust << endl;
//     }
//   }
//   char *getEadresa() {
//     return e_adresa;
//   }
//   int getProizvodi() {
//     return br_proizvodi;
//   }
//   void setType(typeC vid) {
//     this->vid=vid;
//   }
// };
//
// class FINKI_bookstore {
// private:
//   Customer *niza;
//   int n;
// public:
//   FINKI_bookstore(Customer *niza=nullptr, int n=0) {
//     this->n=n;
//     this->niza=new Customer[n];
//     for (int i=0; i<n; i++) {
//       this->niza[i]=niza[i];
//     }
//   }
//   FINKI_bookstore(const FINKI_bookstore &b) {
//     this->n=b.n;
//     this->niza=new Customer[n];
//     for (int i=0; i<n; i++) {
//       this->niza[i]=b.niza[i];
//     }
//   }
//   ~FINKI_bookstore() {
//     delete [] niza;
//   }
//   void setCustomers(Customer *niza, int n) {
//     this->n=n;
//     this->niza=new Customer[n];
//     for (int i=0; i<n; i++) {
//       this->niza[i]=niza[i];
//     }
//   }
//   FINKI_bookstore& operator=(const FINKI_bookstore &b) {
//     if (this!=&b) {
//       delete [] niza;
//       this->n=b.n;
//       this->niza=new Customer[n];
//       for (int i=0; i<n; i++) {
//         this->niza[i]=b.niza[i];
//       }
//     }
//     return *this;
//   }
//   FINKI_bookstore& operator+=(Customer &c) {
//     bool b;
//     for (int i=0; i<n; i++) {
//       if (strcmp(niza[i].getEadresa(), c.getEadresa()) == 0) {
//         b=true;
//       }
//     }
//     if (b) {
//       throw UserExistsException();
//     }
//     Customer *tmp=new Customer[n+1];
//     for (int i=0; i<n; i++) {
//       tmp[i]=niza[i];
//     }
//     tmp[n]=c;
//     delete [] niza;
//     this->niza=tmp;
//     n++;
//     return *this;
//   }
//   friend ostream& operator<<(ostream &out, FINKI_bookstore &b) {
//     for (int i=0; i<b.n; i++) {
//       out << b.niza[i];
//     }
//     return out;
//   }
//   void update() {
//     for (int i=0; i<n; i++) {
//       if (niza[i].getProizvodi()>5 && niza[i].getProizvodi()<10) {
//         niza[i].setType(loyal);
//       }
//       else if (niza[i].getProizvodi()>10) {
//         niza[i].setType(vip);
//       }
//     }
//   }
// };
//
// double Customer::osnoven_popust=10.0;
// double Customer::dopolnitelen_popust=20.0;
//
// int main(){
//   int testCase;
//   cin >> testCase;
//
//   char name[MAX];
//   char email[MAX];
//   int tC;
//   int discount;
//   int numProducts;
//
//
//   if (testCase == 1){
//     cout << "===== Test Case - Customer Class ======" << endl;
//     cin.get();
//     cin.getline(name,MAX);
//     cin.getline(email,MAX);
//     cin >> tC;
//     cin >> numProducts;
//     cout << "===== CONSTRUCTOR ======" << endl;
//     Customer c(name, email, (typeC) tC, numProducts);
//     cout << c;
//
//   }
//
//   if (testCase == 2){
//     cout << "===== Test Case - Static Members ======" << endl;
//     cin.get();
//     cin.getline(name,MAX);
//     cin.getline(email,MAX);
//     cin >> tC;
//     cin >> numProducts;
//     cout << "===== CONSTRUCTOR ======" << endl;
//     Customer c(name, email, (typeC) tC, numProducts);
//     cout << c;
//
//     c.setDiscount1(5);
//
//     cout << c;
//   }
//
//   if (testCase == 3){
//     cout << "===== Test Case - FINKI-bookstore ======" << endl;
//     FINKI_bookstore fc;
//     int n;
//     cin >> n;
//     Customer customers[MAX];
//     for(int i = 0; i < n; ++i) {
//       cin.get();
//       cin.getline(name,MAX);
//       cin.getline(email,MAX);
//       cin >> tC;
//       cin >> numProducts;
//       Customer c(name, email, (typeC) tC, numProducts);
//       customers[i] = c;
//     }
//
//     fc.setCustomers(customers, n);
//
//     cout << fc <<endl;
//   }
//
//   if (testCase == 4){
//     cout << "===== Test Case - operator+= ======" << endl;
//     FINKI_bookstore fc;
//     int n;
//     cin >> n;
//     Customer customers[MAX];
//     for(int i = 0; i < n; ++i) {
//       cin.get();
//       cin.getline(name,MAX);
//       cin.getline(email,MAX);
//       cin >> tC;
//       cin >> numProducts;
//       try {
//         Customer c(name, email, (typeC) tC, numProducts);
//         customers[i] = c;
//       }
//       catch (UserExistsException e) {
//         e.print();
//       }
//     }
//
//     fc.setCustomers(customers, n);
//     cout << "OPERATOR +=" << endl;
//     cin.get();
//     cin.getline(name,MAX);
//     cin.getline(email,MAX);
//     cin >> tC;
//     cin >> numProducts;
//     try {
//       Customer c(name, email, (typeC) tC, numProducts);
//       fc+=c;
//     }
//     catch (UserExistsException e) {
//       e.print();
//     }
//
//     cout << fc;
//   }
//
//   if (testCase == 5){
//     cout << "===== Test Case - operator+= (exception!!!) ======" << endl;
//     FINKI_bookstore fc;
//     int n;
//     cin >> n;
//     Customer customers[MAX];
//     for(int i = 0; i < n; ++i) {
//       cin.get();
//       cin.getline(name,MAX);
//       cin.getline(email,MAX);
//       cin >> tC;
//       cin >> numProducts;
//       try {
//         Customer c(name, email, (typeC) tC, numProducts);
//         customers[i] = c;
//       }
//       catch (UserExistsException e) {
//         e.print();
//       }
//     }
//
//     fc.setCustomers(customers, n);
//     cout << "OPERATOR +=" << endl;
//     cin.get();
//     cin.getline(name,MAX);
//     cin.getline(email,MAX);
//     cin >> tC;
//     cin >> numProducts;
//
//     fc+=c;
//
//     cout << fc;
//   }
//
//   if (testCase == 6){
//     cout << "===== Test Case - update method  ======" << endl << endl;
//     FINKI_bookstore fc;
//     int n;
//     cin >> n;
//     Customer customers[MAX];
//     for(int i = 0; i < n; ++i) {
//       cin.get();
//       cin.getline(name,MAX);
//       cin.getline(email,MAX);
//       cin >> tC;
//       cin >> numProducts;
//       Customer c(name, email, (typeC) tC, numProducts);
//       customers[i] = c;
//     }
//
//     fc.setCustomers(customers, n);
//
//     cout << "Update:" << endl;
//     fc.update();
//     cout << fc;
//   }
//   return 0;
//
// }
// */


/*#include<iostream>
#include<string.h>

using namespace std;

class Delo {
private:
    char ime[50];
    int godina;
    char zemja[50];
public:
    Delo(char *ime="", int godina=0, char zemja[50]="") {
        strcpy(this->ime,ime);
        this->godina=godina;
        strcpy(this->zemja,zemja);
    }
    Delo(const Delo &d) {
        strcpy(this->ime,d.ime);
        this->godina=d.godina;
        strcpy(this->zemja,d.zemja);
    }
    bool operator==(const Delo &d) {
        if (strcmp(this->ime,d.ime)==0) {
            return true;
        }
        return false;
    }
    void setime(char *ime) {
        strcpy(this->ime,ime);
    }
    void setgodina(int godina) {
        this->godina=godina;
    }
    void setzemja(char *zemja) {
        strcpy(this->zemja,zemja);
    }
    char *getIme() {
        return this->ime;
    }
    int getgodina() {
        return this->godina;
    }
    char *getzemja() {
        return this->zemja;
    }
};

class Pretstava {
protected:
    Delo delo;
    int karti;
    char data[15];
public:
    Pretstava(Delo delo=nullptr, int karti=0, char *data="") {
        this->delo=delo;
        this->karti=karti;
        strcpy(this->data,data);
    }
    Pretstava(const Pretstava &p) {
        this->delo=p.delo;
        this->karti=p.karti;
        strcpy(this->data,p.data);
    }
    Delo getDelo() {
        return this->delo;
    }
    int getBrojKarti() {
        return this->karti;
    }
    virtual int cena() {
        int n=0, m=0;
        if (delo.getgodina()>=1900) {
            m=50;
        }
        else if (delo.getgodina()>=1800) {
            m=75;
        }
        else {
            m=100;
        }
        if (strcmp(delo.getzemja(), "Italija")==0) {
            n=100;
        }
        else if (strcmp(delo.getzemja(), "Rusija")==0) {
            n=150;
        }
        else {
            n=80;
        }
        return n+m;
    }
};

class Opera:public Pretstava {
public:
    Opera(Delo delo=nullptr, int karti=0, char *data=""):Pretstava(delo, karti, data) {}
    Opera(const Pretstava &p):Pretstava(p){}
};

class Balet:public Pretstava {
public:
    static int cena_na_karta;
    Balet(Delo delo=nullptr, int karti=0, char *data=""):Pretstava(delo, karti, data){}
    Balet(const Pretstava &p):Pretstava(p){}
    static int setCenaBalet(int c) {
        cena_na_karta=c;
    }
    int cena() override {
        return Pretstava::cena() + cena_na_karta;
    }
};

int Balet::cena_na_karta=150;

float prihod(Pretstava **p, int n) {
    float total = 0;
    for (int i = 0; i < n; i++) {
        total += p[i]->cena() * p[i]->getBrojKarti();
    }
    return total;
}

int brojPretstaviNaDelo(Pretstava **p, int n, Delo d) {
    int br=0;
    for (int i=0;i<n;i++) {
        if (p[i]->getDelo() == d) {
            br++;
        }
    }
    return br;
}


//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
    case 1:
    //Testiranje na klasite Opera i Balet
    {
        cout<<"======TEST CASE 1======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->getDelo().getIme()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->getDelo().getIme()<<endl;
    }break;

    case 2:
    //Testiranje na  klasite Opera i Balet so cena
    {
        cout<<"======TEST CASE 2======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->cena()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->cena()<<endl;
    }break;

    case 3:
    //Testiranje na operator ==
    {
        cout<<"======TEST CASE 3======="<<endl;
        Delo f1=readDelo();
        Delo f2=readDelo();
        Delo f3=readDelo();

        if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

    }break;

    case 4:
    //testiranje na funkcijata prihod
    {
        cout<<"======TEST CASE 4======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();

        }
        cout<<prihod(pole,n);
    }break;

    case 5:
    //testiranje na prihod so izmena na cena za 3d proekcii
    {
        cout<<"======TEST CASE 5======="<<endl;
        int cenaBalet;
        cin>>cenaBalet;
        Balet::setCenaBalet(cenaBalet);
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        cout<<prihod(pole,n);
        }break;

    case 6:
    //testiranje na brojPretstaviNaDelo
    {
        cout<<"======TEST CASE 6======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }

        Delo f=readDelo();
        cout<<brojPretstaviNaDelo(pole,n,f);
    }break;

    };
return 0;
}
*/



/*#include <iostream>      //ZADACA 16
#include <cstring>

using namespace std;

class Transport {
protected:
    char destinacija[20];
    int cena;
    int rastojanie;
public:
    Transport(char *destinacija="", int cena=0, int rastojanie=0) {
        strcpy(this->destinacija, destinacija);
        this->cena = cena;
        this->rastojanie=rastojanie;
    }
    Transport(const Transport &t) {
        strcpy(this->destinacija, t.destinacija);
        this->cena = t.cena;
        this->rastojanie = t.rastojanie;
    }
    virtual double cenaTransport()=0;
    virtual bool operator<(const Transport &t)=0;
    int getRastojanie() const {
        return this->rastojanie;
    }

    const char *getDestinacija() const {
        return this->destinacija;
    }
};

class AvtomobilTransport:public Transport {
private:
    bool sofer;
public:
    AvtomobilTransport(char *destinacija="", int cena=0, int rastojanie=0, bool sofer=false):Transport(destinacija, cena, rastojanie) {
        this->sofer=sofer;
    }
    AvtomobilTransport(const AvtomobilTransport &t):Transport(t) {
        this->sofer=t.sofer;
    }
    double cenaTransport() override {
        if (sofer) {
            return cena*1.2;
        }
        return cena;
    }
    bool operator<(const Transport &t) override{
        if (this->rastojanie<t.getRastojanie()) {
            return true;
        }
        return false;
    }
};

class KombeTransport:public Transport {
private:
    int br_lugje;
public:
    KombeTransport(char *destinacija="", int cena=0, int rastojanie=0, int br_lugje=0):Transport(destinacija, cena, rastojanie) {
        this->br_lugje=br_lugje;
    }
    KombeTransport(const KombeTransport &t):Transport(t) {
        this->br_lugje=t.br_lugje;
    }
    double cenaTransport() override {
        return cena-(br_lugje*200);
    }
    bool operator<(const Transport &t) override{
        if (this->rastojanie<t.getRastojanie()) {
            return true;
        }
        return false;
    }
};

void pecatiPoloshiPonudi(Transport **ponudi, int n, Transport &t) {
    Transport **poloshi = new Transport *[n];
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (ponudi[i]->cenaTransport() > t.cenaTransport()) {
            poloshi[count++] = ponudi[i];
        }
    }
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (poloshi[i]->getRastojanie() > poloshi[j]->getRastojanie()) {
                Transport *tmp = poloshi[i];
                poloshi[i] = poloshi[j];
                poloshi[j] = tmp;
            }
        }
    }
    for (int i = 0; i < count; i++) {
        cout << poloshi[i]->getDestinacija() << " " << poloshi[i]->getRastojanie() << " " << poloshi[i]->cenaTransport() << endl;
    }
    delete[] poloshi;
}



int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
*/


/*#include <iostream>    //ZADACA 14
#include <cstring>
#include <cmath>

using namespace std;

class SMS {
protected:
    double cena;
    char broj[20];
public:
    SMS(char *broj = "", double cena = 0.0) {
        this->cena = cena;
        strcpy(this->broj, broj);
    }
    SMS(const SMS &other) {
        this->cena = other.cena;
        strcpy(this->broj, other.broj);
    }
    virtual double SMS_cena() = 0;
    virtual void print(ostream &out) const = 0;

    friend ostream &operator<<(ostream &out, SMS &s) {
        s.print(out);
        return out;
    }

    virtual ~SMS() {}
};

class RegularSMS : public SMS {
private:
    char msg[1000];
    bool roam;
    static int rProcent;
public:
    RegularSMS():SMS() {
        this->roam = false;
        strcpy(this->msg, "");
    }
    RegularSMS(char *broj, double cena, char *msg, bool roam):SMS(broj, cena) {
        strcpy(this->msg, msg);
        this->roam = roam;
    }
    RegularSMS(const RegularSMS &other):SMS(other) {
        this->roam = other.roam;
        strcpy(this->msg, other.msg);
    }

    static void set_rProcent(int p) {
        rProcent = p;
    }

    double SMS_cena() override {
        double parts = strlen(msg) / 160;
        if (strlen(msg) % 160 != 0) parts++;
        double finalCena = cena;
        if (roam) {
            finalCena += cena * rProcent / 100.0;
        } else {
            finalCena += cena * 0.18;
        }
        return finalCena * parts;
    }

    void print(ostream &out) const override {
        out << "Tel: " << broj << " - cena: " << ((RegularSMS*)this)->SMS_cena() << "den." << endl;
    }
};

int RegularSMS::rProcent = 300;

class SpecialSMS : public SMS {
private:
    bool hum;
    static int sProcent;
public:
    SpecialSMS():SMS() {
        this->hum = false;
    }
    SpecialSMS(char *broj, double cena, bool hum):SMS(broj, cena) {
        this->hum = hum;
    }
    SpecialSMS(const SpecialSMS &other):SMS(other) {
        this->hum = other.hum;
    }

    static void set_sProcent(int p) {
        sProcent = p;
    }

    double SMS_cena() override {
        double finalCena = cena;
        if (!hum) {
            finalCena += cena * sProcent / 100.0;
        }
        return finalCena;
    }

    void print(ostream &out) const override {
        out << "Tel: " << broj << " - cena: " << ((SpecialSMS*)this)->SMS_cena() << "den." << endl;
    }
};

int SpecialSMS::sProcent = 150;

void vkupno_SMS(SMS **poraka, int n) {
    int regCount = 0, specCount = 0;
    double regTotal = 0, specTotal = 0;

    for (int i = 0; i < n; i++) {
        RegularSMS *r = dynamic_cast<RegularSMS*>(poraka[i]);
        SpecialSMS *s = dynamic_cast<SpecialSMS*>(poraka[i]);

        if (r) {
            regCount++;
            regTotal += r->SMS_cena();
        } else if (s) {
            specCount++;
            specTotal += s->SMS_cena();
        }
    }

    cout << "Vkupno ima " << regCount << " regularni SMS poraki i nivnata cena e: " << regTotal << endl;
    cout << "Vkupno ima " << specCount << " specijalni SMS poraki i nivnata cena e: " << specTotal << endl;
}


int main(){

	char tel[20], msg[1000];
	float cena;
	float price;
    int p;
	bool roam, hum;
	SMS  **sms;
	int n;
	int tip;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing RegularSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new RegularSMS(tel, cena, msg, roam);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 2){
		cout << "====== Testing SpecialSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
			cin >> hum;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new SpecialSMS(tel, cena, hum);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 3){
		cout << "====== Testing method vkupno_SMS() ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i<n; i++){

			cin >> tip;
			cin >> tel;
			cin >> cena;
			if (tip == 1) {

				cin.get();
				cin.getline(msg, 1000);
                cin >> roam;

				sms[i] = new RegularSMS(tel, cena, msg, roam);

			}
			else {
				cin >> hum;

				sms[i] = new SpecialSMS(tel, cena, hum);
			}
		}

		vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
    if (testCase == 4){
		cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			sms1 = new RegularSMS(tel, cena, msg, roam);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
        	cin >> p;
        	RegularSMS::set_rProcent(p);
        	sms2 = new RegularSMS(tel, cena, msg, roam);
        	cout << *sms2;

        delete sms1, sms2;
	}
    if (testCase == 5){
		cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
			cin >> hum;
			sms1 = new SpecialSMS(tel, cena, hum);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
			cin >> hum;
        	cin >> p;
        	SpecialSMS::set_sProcent(p);
        	sms2 = new SpecialSMS(tel, cena, hum);
        	cout << *sms2;

        delete sms1, sms2;
	}

	return 0;
}
*/



/*   //ZADACA 12
 *#include <iostream>
#include <cstring>
using namespace std;

enum tip {Mobilen, Laptop};

class InvalidProductionDate {
public:
    void pecati() const {
        cout << "Невалидна година на производство" << endl;
    }
};

class Device {
private:
    char model[100];
    tip deviceType;
    int godina;
    static float pocetniCasovi;

public:
    Device(const char* model = "", tip deviceType = Mobilen, int godina = 2000) {
        strcpy(this->model, model);
        this->deviceType = deviceType;
        this->godina = godina;
    }

    static void setPocetniCasovi(float casovi) {
        pocetniCasovi = casovi;
    }

    float presmetajCasovi() const {
        float vkupno = pocetniCasovi;
        if (godina > 2015)
            vkupno += 2;
        if (deviceType == Laptop)
            vkupno += 2;
        return vkupno;
    }

    const int getGodina() const {
        return godina;
    }

    friend ostream& operator<<(ostream& os, const Device& d) {
        os << d.model << endl;
        os << (d.deviceType == Laptop ? "Laptop " : "Mobilen ");
        os << d.presmetajCasovi() << endl;
        return os;
    }
};

float Device::pocetniCasovi = 1.0;

class MobileServis {
private:
    char adresa[100];
    Device* devices;
    int n;

public:
    MobileServis(const char* adresa = "") {
        strcpy(this->adresa, adresa);
        devices = nullptr;
        n = 0;
    }

    ~MobileServis() {
        delete[] devices;
    }

    MobileServis(const MobileServis& other) {
        strcpy(this->adresa, other.adresa);
        this->n = other.n;
        this->devices = new Device[n];
        for (int i = 0; i < n; i++)
            this->devices[i] = other.devices[i];
    }

    MobileServis& operator=(const MobileServis& other) {
        if (this != &other) {
            delete[] devices;
            strcpy(this->adresa, other.adresa);
            this->n = other.n;
            this->devices = new Device[n];
            for (int i = 0; i < n; i++)
                this->devices[i] = other.devices[i];
        }
        return *this;
    }

    MobileServis& operator+=(const Device& d) {
        if (d.getGodina() < 2000 || d.getGodina() > 2019) {
            InvalidProductionDate e;
            e.pecati();
            return *this;
        }
        Device* tmp = new Device[n + 1];
        for (int i = 0; i < n; i++)
            tmp[i] = devices[i];
        tmp[n++] = d;
        delete[] devices;
        devices = tmp;
        return *this;
    }

    void pecatiCasovi() const {
        cout << "Ime: " << adresa << endl;
        for (int i = 0; i < n; i++)
            cout << devices[i];
    }
};

int main()
{
	int testCase;
	cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> tipDevice;
		cin >> godina;
		Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
		MobileServis t(ime);
        cout<<ig;
		}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
	}
	if (testCase == 3){
		cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
	}
	if (testCase == 4){
		cout <<"===== Testiranje na konstruktori ======"<<endl;
		 cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}
	if (testCase == 5){
		cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            t+=tmp;
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
		Device::setPocetniCasovi(2);
        t.pecatiCasovi();
	}

		if (testCase == 6){
		cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
		cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
		Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}

	return 0;

}
*/