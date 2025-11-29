#include <iostream>
#include <cstring>
using namespace std;
class Ekipa {
private:
    char ime[20];
    int godina;
    char grad[20];
public:
    Ekipa() {}
    Ekipa(char _ime[],int _godina,char _grad[]) {
        strcpy(ime,_ime);
        godina=_godina;
        strcpy(grad,_grad);
    }
    const char *getIme() const {
        return ime;
    }
    const int getGodina() const {
        return godina;
    }
    const char *getGrad() const {
        return grad;
    }
    void print() {
        cout<<ime<<" "<<grad<<" "<<godina<<endl;
    }
    bool isEqual(const Ekipa other) const{
        return strcmp(ime,other.ime)==0;
    }
    ~Ekipa(){}
};
class Natprevar {
    private:
    Ekipa gostin;
    Ekipa domakin;
    int gol_gostin;
    int gol_domakin;
public:
    Natprevar(){}
    Natprevar(const Ekipa g,const Ekipa d,int g_g,int g_d) {
        gostin=g;
        domakin=d;
        gol_gostin=g_g;
        gol_domakin=g_d;
    }
    const Ekipa getGostin() const{
        return gostin;
    }
    const Ekipa getDomakin() const {
        return domakin;
    }
    const int getGolgostin() const{
        return gol_gostin;
    }
    const int getGoldomakin() const {
        return gol_domakin;
    }
    ~Natprevar(){}
};
bool revans(const Natprevar prv,const Natprevar vtor) {
    return prv.getGostin().isEqual(vtor.getDomakin()) && prv.getDomakin().isEqual(vtor.getGostin());
}
Ekipa duel(const Natprevar prv,const Natprevar vtor) {
    if(revans(prv,vtor)) {
        int eGolovi1 = prv.getGoldomakin() + vtor.getGolgostin();
        int eGolovi2 = vtor.getGoldomakin() + prv.getGolgostin();
        if (eGolovi1 > eGolovi2) {
            return prv.getDomakin();
        }
        else if (eGolovi1 < eGolovi2) {
            return prv.getGostin();
        }
        else if (prv.getGolgostin() > vtor.getGolgostin()) {
            return prv.getGostin();
        }
        else if (prv.getGolgostin() < vtor.getGolgostin()) {
            return vtor.getDomakin();
        }
        else {
            cout<<"0"<<endl;
        }
    }
    else {
        cout<<"Ne se sovpagjaat"<<endl;
    }
}
int main()
{
    char ime1[20], ime2[20], grad1[20], grad2[20];
    int godina1, godina2;
    int gol_gostin1, gol_domakin1, gol_gostin2, gol_domakin2;

    cin >> ime1 >> grad1 >> godina1;
    Ekipa ekipa1(ime1, godina1, grad1);

    cin >> ime2 >> grad2 >> godina2;
    Ekipa ekipa2(ime2, godina2, grad2);

    cin >> gol_gostin1 >> gol_domakin1;
    Natprevar n1(ekipa1, ekipa2, gol_gostin1, gol_domakin1);

    cin >> gol_gostin2 >> gol_domakin2;
    Natprevar n2(ekipa2, ekipa1, gol_gostin2, gol_domakin2);

    cout << revans(n1, n2) << endl;
    cout << duel(n1, n2).getIme() << endl;
    return 0;
}
