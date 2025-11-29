#include <iostream>
#include <cstring>

using namespace std;

class FudblaskaEkipa {
protected:
    char ime_tr[100];
    int golovi[10];
public:
    FudblaskaEkipa() {
        strcpy(ime_tr,"");
    }
    FudblaskaEkipa(char *ime_tr, int golovi[]) {
        strcpy(this->ime_tr,ime_tr);
        for (int i = 0; i < 10; i++) {
            this->golovi[i] = golovi[i];
        }
    }
    virtual int uspeh()=0;
};

class Klub:public FudblaskaEkipa{
private:
    char ime[100];
    int tituli;
public:
    Klub():FudblaskaEkipa() {
        strcpy(ime,"");
        tituli=0;
    }
    Klub(char *ime_tr, int golovi[], char *ime, int tituli):FudblaskaEkipa(ime_tr, golovi) {
        this->tituli=tituli;
        strcpy(this->ime,ime);
    }
    int uspeh()override {
        int zbir=0;
        for (int i = 0; i < 10; i++) {
            zbir+=this->golovi[i];
        }
        return zbir*3+tituli*1000;
    }

    friend ostream& operator<<(ostream& os, Klub& klub) {
        os << klub.ime << endl << klub.ime_tr << endl << klub.uspeh() << endl;
    }
};

class Reprezentacija:public FudblaskaEkipa{
private:
    char ime[100];
    int nastani;
public:
    Reprezentacija():FudblaskaEkipa() {
        strcpy(ime,"");
        nastani=0;
    }
    Reprezentacija(char *ime_tr, int golovi[], char *ime, int nastani):FudblaskaEkipa(ime_tr, golovi) {
        this->nastani=nastani;
        strcpy(this->ime,ime);
    }
    int uspeh() override {
        int zbir=0;
        for (int i = 0; i < 10; i++) {
            zbir+=this->golovi[i];
        }
        return zbir*3+nastani*50;
    }
    friend ostream& operator<<(ostream& os, Reprezentacija& r) {
        os << r.ime << endl << r.ime_tr << endl << r.uspeh() << endl;
    }
};

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}
