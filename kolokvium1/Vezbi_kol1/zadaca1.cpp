#include <iostream>
#include <cstring>

using namespace std;

enum tip{pop, rap, rock};

class Pesna {
private:
    char *ime;
    int vremetraenje;
    tip t;
public:
    Pesna() {
    	ime = new char[1];
    	ime[0] = '\0';
        vremetraenje = 0;
        t = pop;
    }
    Pesna(char *ime, int vremetraenje, tip t) {
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->vremetraenje=vremetraenje;
        this->t=t;
    }
    Pesna(const Pesna &p) {
        this->ime=new char[strlen(p.ime)+1];
        strcpy(this->ime,p.ime);
        this->vremetraenje=p.vremetraenje;
        this->t=p.t;
    }
	Pesna& operator=(const Pesna &p) {
    	if (this != &p) {
    		delete[] ime;
    		ime = new char[strlen(p.ime) + 1];
    		strcpy(ime, p.ime);
    		vremetraenje = p.vremetraenje;
    		t = p.t;
    	}
    	return *this;
    }
	~Pesna() {
	    delete [] ime;
    }
	tip getTip() {
	    return t;
    }
    void pecati() {
        cout << "\"" << ime << "\"-" << vremetraenje << "min" << endl;
    }
	float get_vreme() {
	    return vremetraenje;
    }
};

class CD {
private:
	int br;
	int max_vt;
	Pesna pesni[10];
public:
	CD() {
		br=0;
		max_vt=0;
	}
	CD(int max_vt) {
        this->br = 0;
        this->max_vt = max_vt;
    }
	CD(int br, int max_vt, Pesna pesni[]) {
		this->br=br;
		this->max_vt=max_vt;
		for (int i=0;i<br;i++) {
			this->pesni[i]=pesni[i];
		}
	}
	Pesna getPesna(int n) const {
		if (n >= 0 && n < br) {
			return pesni[n];
		}
		return Pesna();
	}
	int getBroj() {
		return br;
	}
	void dodadiPesna(Pesna p) {
		if (br<10) {
			float vreme=0;
			for(int i=0;i<br;i++) {
				vreme+=pesni[i].get_vreme();
			}
			if (vreme+p.get_vreme()<=max_vt) {
				pesni[br]=p;
				br++;
			}
		}
	}
	void pecatiPesniPoTip(tip t) {
		for (int i=0;i<br;i++) {
			if (pesni[i].getTip()==t) {
				pesni[i].pecati();
			}
		}
	}
};

int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, minuti, kojtip;
	char ime[50];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
		p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<n; i++)
				(omileno.getPesna(i)).pecati();
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<omileno.getBroj(); i++)
				(omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

return 0;
}