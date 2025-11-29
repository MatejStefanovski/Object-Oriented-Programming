#include <iostream>
#include <cstring>

using namespace std;

struct Voz {
    char relacija[50];
    double kilometri;
    int brojPatnici;
};

struct ZeleznickaStanica {
    char grad[20];
    Voz vozovi[30];
    int brojVozovi;
};

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad) {
    double minKm = -1;
    char najkratkaRelacija[50];

    for (int i = 0; i < n; i++) {
        if (strcmp(zs[i].grad, grad) == 0) {
            for (int j = 0; j < zs[i].brojVozovi; j++) {
                if (minKm == -1 || zs[i].vozovi[j].kilometri <= minKm) {
                    minKm = zs[i].vozovi[j].kilometri;
                    strcpy(najkratkaRelacija, zs[i].vozovi[j].relacija);
                }
            }
        }
    }

    if (minKm != -1) {
        cout << "Najkratka relacija: " << najkratkaRelacija << " (" << minKm << " km)" << endl;
    }
}

int main() {
    int n;
    cin >> n; // Se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];

    for (int i = 0; i < n; i++) {
        cin >> zStanica[i].grad;
        cin >> zStanica[i].brojVozovi;

        for (int j = 0; j < zStanica[i].brojVozovi; j++) {
            cin >> zStanica[i].vozovi[j].relacija;
            cin >> zStanica[i].vozovi[j].kilometri;
            cin >> zStanica[i].vozovi[j].brojPatnici;
        }
    }

    char grad[25];
    cin >> grad;

    najkratkaRelacija(zStanica, n, grad);

    return 0;
}
