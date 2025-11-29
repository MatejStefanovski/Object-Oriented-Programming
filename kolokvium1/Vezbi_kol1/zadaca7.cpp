#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

struct Vozenje {
    char ime[100];
    int min;
    double cena;
    bool popust;
};

struct ZabavenPark {
    char ime[100];
    char lokacija[100];
    Vozenje niza[100];
    int br;
};

void print(ZabavenPark *z) {
    cout << z->ime << " " << z->lokacija << endl;
    for (int i=0; i<z->br; i++) {
        cout << z->niza[i].ime << " " << z->niza[i].min << " " << fixed << setprecision(2) << z->niza[i].cena << endl;
    }
}

void najdobar_park(ZabavenPark z[], int n) {
    int mx=0, mx2=0;
    ZabavenPark t;
    int vremetraenje[n];
    for (int i=0; i<n; i++) {
        int br=0;
        for (int j=0; j<z[i].br; j++) {
            if (z[i].niza[j].popust==1) {
                br++;
            }
            vremetraenje[i]+=z[i].niza[j].min;
        }
        if (br>mx) {
            mx=br;
            t=z[i];
        }
        else {
            mx2=br;
        }
    }
    if (mx>mx2) {
        cout << "Najdobar park: " << t.ime << " " << t.lokacija << endl;
    }
    else {
        int k=0;
        for (int i=0; i<n; i++) {
            if (vremetraenje[i]>k) {
                k=vremetraenje[i];
                t=z[i];
            }
        }
        cout << "Najdobar park: " << t.ime << " " << t.lokacija << endl;
    }
}

int main() {
    int n;
    cin >> n;
    ZabavenPark p[n];
    for (int i=0; i<n; i++) {
        cin >> p[i].ime;
        cin >> p[i].lokacija;
        cin >> p[i].br;
        for (int j=0; j<p[i].br; j++) {
            cin >> p[i].niza[j].ime;
            cin >> p[i].niza[j].min;
            cin >> p[i].niza[j].cena;
            cin >> p[i].niza[j].popust;
        }
    }
    for (int i=0; i<n; i++) {
        print(&p[i]);
    }
    najdobar_park(p, n);
    return 0;
}
