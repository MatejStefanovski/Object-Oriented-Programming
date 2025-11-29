#include <iostream>
#include <cstring>

using namespace std;

class Momche {
private:
    char ime[50];
    char prezime[50];
    int godini;
public:
    Momche(char *imee, char *prezimee, int godinii) {
        strcpy(ime, imee);
        strcpy(prezime, prezimee);
        godini = godinii;
    }
    ~Momche() {}
    void pecati() {
        cout << "Momche " << ime << " " << prezime << " " << godini << endl;
    }
    int getGodini() {
        return godini;
    }
};

class Devojche {
private:
    char ime[50];
    char prezime[50];
    int godini;
public:
    Devojche(char *imee, char *prezimee, int godinii) {
        strcpy(ime, imee);
        strcpy(prezime, prezimee);
        godini = godinii;
    }
    ~Devojche() {}
    void pecati() {
        cout << "Devojche " << ime << " " << prezime << " " << godini << endl;
    }
    int getGodini() {
        return godini;
    }
};

class Sredba {
private:
    Momche &m;
    Devojche &d;
public:
    Sredba(Momche &m1, Devojche &d1) : m(m1), d(d1) {}
    ~Sredba() {}
    void pecati() {
        cout << "Sredba: ";
        m.pecati();
        d.pecati();
    }
    void daliSiOdgovaraat() {
        if (abs(m.getGodini() - d.getGodini()) < 5)
            cout << "Si odgovaraat" << endl;
        else
            cout << "Ne si odgovaraat" << endl;

    }
};

int main() {
    int godini;
    char ime[20], prezime[20];

    cout << "Informacii za momche: " << endl;
    cout << "Ime: ";
    cin >> ime;
    cout << "Prezime: ";
    cin >> prezime;
    cout << "Godini: ";
    cin >> godini;
    Momche m(ime, prezime, godini);
    Momche momche(m);

    cout << "Informacii za Devojche: " << endl;
    cout << "Ime: ";
    cin >> ime;
    cout << "Prezime: ";
    cin >> prezime;
    cout << "Godini: ";
    cin >> godini;
    Devojche d(ime, prezime, godini);
    Devojche devojche = d;

    Sredba s(momche, devojche);
    s.pecati();
    s.daliSiOdgovaraat();
    return 0;
}
