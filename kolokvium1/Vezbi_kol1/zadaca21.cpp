#include<iostream>
#include <cstring>

using namespace std;

class Tanc {
private:
    char ime[15];
    char zemja[15];
public:
    Tanc() {
        strcpy(ime,"");
        strcpy(zemja,"");
    }
    Tanc (char *ime, char *zemja) {
        strcpy(this->ime,ime);
        strcpy(this->zemja,zemja);
    }
    void set_zemja(char *p) {
        strcpy(zemja,p);
    }
    void set_ime(char *i) {
        strcpy(ime,i);
    }
    char *get_ime() {
        return ime;
    }
    char *get_zemja() {
        return zemja;
    }
};

class Tancer {
private:
    char ime[20];
    char prezime[20];
public:
    Tanc niza[5];
    Tancer() {
        strcpy(ime,"");
        strcpy(prezime,"");
    }
    Tancer(char *ime, char *prezme) {
        strcpy(this->ime,ime);
        strcpy(this->prezime,prezme);
    }
    void set_prezime(char *p) {
        strcpy(prezime,p);
    }
    void set_ime(char *i) {
        strcpy(ime,i);
    }
    char *get_ime() {
        return ime;
    }
    char *get_prezime() {
        return prezime;
    }
};

void tancuvanje(Tancer *t, int n, char *zemja) {
    for (int i = 0; i < n; i++) {
        int a=0;
        char tanc[15];
        for (int j = 0; j < 5; j++) {
            if (strcmp(t[i].niza[j].get_zemja(), zemja) == 0) {
                a=1;
                strcpy(tanc, t[i].niza[j].get_ime());
                tanc[strlen(t[i].niza[j].get_ime())]='\0';
                break;
            }
        }
        if (a==1) {
            cout << t[i].get_ime() << " " << t[i].get_prezime() << ", " << tanc << endl;
        }
    }
}

int main()
{
    int i, j, n;
    char zemja[15];
    Tancer tanceri[5];
    cin >> n;
    for(i = 0; i < n; i++){
        char ime[15], prezime[15];
        cin >> ime;
        cin >> prezime;
        tanceri[i].set_prezime(prezime);
        tanceri[i].set_ime(ime);
        for(j = 0; j < 3; j++){
            char im[15], prez[15];
            cin >> im;
            cin >> prez;
            tanceri[i].niza[j].set_ime(im);
            tanceri[i].niza[j].set_zemja(prez);
        }
    }
    cin >> zemja;
    tancuvanje(tanceri, n, zemja);
    return 0;
}
