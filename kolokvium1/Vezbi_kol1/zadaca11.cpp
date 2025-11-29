#include <iostream>
#include <cstring>

using namespace std;

class Ucesnik {
private:
    char *ime;
    bool pol;
    int vozrast;
public:
    Ucesnik() {
        this->ime = new char[1];
        this->ime[0] = '\0';
        this->pol = false;
        this->vozrast = 0;
    }

    Ucesnik(const char *ime, bool pol, int vozrast) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->pol = pol;
        this->vozrast = vozrast;
    }

    Ucesnik(const Ucesnik &u) {
        this->ime = new char[strlen(u.ime) + 1];
        strcpy(this->ime, u.ime);
        this->pol = u.pol;
        this->vozrast = u.vozrast;
    }

    Ucesnik& operator=(const Ucesnik &u) {
        if (this != &u) {
            delete[] ime;
            this->ime = new char[strlen(u.ime) + 1];
            strcpy(this->ime, u.ime);
            this->pol = u.pol;
            this->vozrast = u.vozrast;
        }
        return *this;
    }

    ~Ucesnik() {
        delete[] ime;
    }

    int getVozrast() const {
        return vozrast;
    }

    bool operator>(const Ucesnik &u) const {
        return this->vozrast > u.vozrast;
    }

    friend ostream &operator<<(ostream &out, const Ucesnik &u) {
        out << u.ime << endl;
        out << (u.pol ? "mashki" : "zhenski") << endl;
        out << u.vozrast << endl;
        return out;
    }

    void pecati() const {
        cout << ime << endl;
        cout << (pol ? "mashki" : "zhenski") << endl;
        cout << vozrast << endl;
    }
};

class Maraton {
private:
    char *lokacija;
    Ucesnik *niza;
    int br;
public:
    Maraton(const char *lokacija) {
        this->lokacija = new char[strlen(lokacija) + 1];
        strcpy(this->lokacija, lokacija);
        this->br = 0;
        this->niza = nullptr;
    }

    Maraton(const char *lokacija, Ucesnik *niza, int br) {
        this->lokacija = new char[strlen(lokacija) + 1];
        strcpy(this->lokacija, lokacija);
        this->br = br;
        this->niza = new Ucesnik[br];
        for (int i = 0; i < br; i++) {
            this->niza[i] = niza[i];
        }
    }

    ~Maraton() {
        delete[] lokacija;
        delete[] niza;
    }

    Maraton& operator+=(const Ucesnik &u) {
        Ucesnik *tmp = new Ucesnik[br + 1];
        for (int i = 0; i < br; i++) {
            tmp[i] = this->niza[i];
        }
        tmp[br] = u;
        delete[] niza;
        niza = tmp;
        br++;
        return *this;
    }

    double prosecnoVozrast() const {
        if (br == 0) return 0.0;
        double suma = 0;
        for (int i = 0; i < br; i++) {
            suma += niza[i].getVozrast();
        }
        return suma / br;
    }

    void pecatiPomladi(const Ucesnik &u) const {
        for (int i = 0; i < br; i++) {
            if (niza[i].getVozrast() < u.getVozrast()) {
                niza[i].pecati();
            }
        }
    }
};

int main() {
    int n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;

    Maraton m(lokacija);

    Ucesnik **u = new Ucesnik*[n];
    for (int i = 0; i < n; ++i) {
        char ime[100];
        bool maski;
        int vozrast;
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }

    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;

    for (int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete[] u;

    return 0;
}
