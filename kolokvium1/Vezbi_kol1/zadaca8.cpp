#include <iostream>
#include <cstring>

using namespace std;

struct Laptop {
    char firma[100];
    double golemina;
    bool touch;
    int cena;
};

struct ITStore {
    char ime[100];
    char lokacija[100];
    Laptop niza[100];
    int br;
};

void print(ITStore store) {
    cout << store.ime << " " << store.lokacija << endl;
    for (int i=0; i < store.br; i++) {
        cout << store.niza[i].firma << " " << store.niza[i].golemina << " " << store.niza[i].cena << endl;
    }
}

void najeftina_ponuda(ITStore store[], int n) {
    int najniska_cena=999999;
    ITStore kraj;
    for (int i=0; i < n; i++) {
        for (int j=0; j<store[i].br; j++) {
            if (store[i].niza[j].touch && store[i].niza[j].cena<najniska_cena) {
                najniska_cena=store[i].niza[j].cena;
                kraj=store[i];
            }
        }
    }
    cout << "Najeftina ponuda ima prodavnicata:" << endl;
    cout << kraj.ime << " " << kraj.lokacija << endl;
    cout << "Najniskata cena iznesuva: " << najniska_cena << endl;
}

int main() {
    ITStore s[100];
    int n;
    cin >> n;

    for (int i=0; i < n; i++) {
        cin >> s[i].ime;
        cin >> s[i].lokacija;
        cin >> s[i].br;
        for (int j=0; j < s[i].br; j++) {
            cin >> s[i].niza[j].firma;
            cin >> s[i].niza[j].golemina;
            int temp;
            cin >> temp;
            if (temp==1) {
                s[i].niza[j].touch=true;
            }
            else {
                s[i].niza[j].touch=false;
            }
            cin >> s[i].niza[j].cena;
        }
    }

    for (int i=0; i < n; i++) {
        print(s[i]);
    }

    najeftina_ponuda(s, n);
    return 0;
}
