#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Date {
private:
    int d,m,y;
public:
    Date(){}
    Date(int dd, int mm, int yy) {
        d = dd;
        m = mm;
        y = yy;
    }
    ~Date(){}
    bool compare(Date &date) {
        return y == date.y && m == date.m && d == date.d;
    }
    friend ostream &operator<<(ostream &out, Date & f){
        out<< f.d << "/" << f.m << "/" << f.y;
        return out;
    }
    friend istream &operator>>(istream &in, Date & f) {
        in >> f.d >> f.m >> f.y;
        return in;
    }
    void read(ifstream &in) {
        in >> d >> m >> y;
        in.ignore();
    }
};

class Call {
private:
    string telefon;
    int vremetraenje;
    Date datum;
public:
    Call() {
        telefon = "";
        vremetraenje = 0;
    }
    Call(string telefon, int vremetraenje, Date datum) {
        this->telefon = telefon;
        this->vremetraenje = vremetraenje;
        this->datum = datum;
    }
    friend ostream &operator<<(ostream &out, Call & f) {
        out << "Dialed number: " << f.telefon << " " << f.vremetraenje << " sec, " << f.datum << endl;
        return out;
    }
    void read(ifstream& in) {
        in >> datum >> telefon >> vremetraenje;
        in.ignore();
    }
    string getTelefon() {
        return telefon;
    }
    int getVremetraenje() {
        return vremetraenje;
    }
    Date getDatum() {
        return datum;
    }
    void setTelefon(string telefon) {
        this->telefon = telefon;
    }
    void setVremetraenje(int vremetraenje) {
        this->vremetraenje = vremetraenje;
    }
    void setDatum(Date datum) {
        this->datum = datum;
    }
};

class Log {
private:
    Call *povici;
    int n;
public:
    Log() {
        n=0;
        this->povici = new Call[10];
    }
    Log(Call *povici, int n) {
        this->n=n;
        this->povici=new Call[n+1];
        for (int i=0;i<n;i++) {
            this->povici[i] = povici[i];
        }
    }
    ~Log() {
        delete[] povici;
    }
    void read(ifstream &in) {
        in >> n;
        delete[] povici;
        povici = new Call[n];
        for (int i = 0; i < n; i++) {
            povici[i].read(in);
        }
    }
    friend ostream &operator<<(ostream &out, Log & f) {
        for (int i=0; i<f.n;i++) {
            out << f.povici[i];
        }
        return out;
    }
    Log daily(Date d) {
        int count=0;
        for (int i=0;i<n;i++) {
            if (povici[i].getDatum().compare(d)) {
                count++;
            }
        }
        int j=0;
        Call *tmp=new Call[count];
        for (int i=0;i<n;i++) {
            if (povici[i].getDatum().compare(d)) {
                tmp[j]=povici[i];
                j++;
            }
        }
        return Log(tmp,j);
    }
};

void wtf() {
    ofstream fout("prva.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----"){
            break;
        }
        fout << line << endl;
    }
}
void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}
int main() {
    wtf();
    ifstream fin("prva.txt");
    ofstream fout("vtora.txt");
    ofstream fout2("treta.txt");
    Log log;
    log.read(fin);
    fin.close();
    fout<<log;
    fout.close();
    Date d;
    cin >> d;
    Log log1 = log.daily(d);
    fout2 << log1;
    fout2.close();
    cout << "All the data for the log:" << endl;
    rff("vtora.txt");
    cout << "Calls on date " << d << endl;
    rff("treta.txt");
    return 0;
}


/*#include <iostream>
#include <string>

using namespace std;

class InvalidSerialNumberFormatException {
private:
    string serialNumber;
public:
    InvalidSerialNumberFormatException(string serialNumber) {
        this->serialNumber = serialNumber;
    }
    void print() {
        cout << "The serial number: " << serialNumber << " is invalid machine serial number format" << endl;
    }
};

class Machine {
protected:
    string model;
    int potrosuvacka;
    float cena;
    string seriski_br;
public:
    Machine(string model="", int potrosuvacka=0, string seriski_br="", float cena=0.0) {
        int prazni_mesta=0;
        for (int i=0; i<seriski_br.length(); i++) {
            if (isspace(seriski_br[i])) {
                prazni_mesta++;
            }
        }
        if (seriski_br.length() != 12 || prazni_mesta>0) {
            throw InvalidSerialNumberFormatException(seriski_br);
        }
        this->model = model;
        this->potrosuvacka = potrosuvacka;
        this->cena = cena;
        this->seriski_br = seriski_br;
    }
    Machine(const Machine &other) {
        this->model = other.model;
        this->potrosuvacka = other.potrosuvacka;
        this->cena = other.cena;
        this->seriski_br = other.seriski_br;
    }
    virtual float calculateCost()=0;
    virtual void showDetails()=0;
};

class WashingMachine:public Machine {
private:
    int tovar;
public:
    WashingMachine(string model="", int potrosuvacka=0, string seriski_br="", float cena=500, int tovar=0):Machine(model, potrosuvacka, seriski_br, cena) {
        this->tovar = tovar;
    }
    float calculateCost() override {
        if (tovar>8) {
            int c=cena*1.12;
            return  (potrosuvacka/100)*20+c;
        }
    }
    void showDetails() override {
        cout << "Washing Machine " << model << " cost: " << calculateCost() << "$" << endl;
    }
};

class DryingMachine:public Machine {
private:
    bool sensor;
public:
    DryingMachine(string model="", int potrosuvacka=0, string seriski_br="", float cena=500, bool sensor=false):Machine(model, potrosuvacka, seriski_br, cena) {
        this->sensor = sensor;
    }
    float calculateCost() override {
        if (sensor) {
            int c=cena*1.15;
            return  (potrosuvacka/100)*25+c;
        }
    }
    void showDetails() override {
        cout << "Drying Machine " << model << " cost: " << calculateCost() << "$" << endl;
    }
};

Machine **createMachines(int &n) {
    Machine **machines = new Machine *[n];
    string model, serialNumber;
    int t, powerConsumption, value;

    for (int i = 0; i < n; i++) {
        cin >> t;
        cin >> model >> powerConsumption >> serialNumber >> value;

        try {
            machines[i] = (t == 1)
                ? static_cast<Machine *>(new WashingMachine(model, powerConsumption, serialNumber, value))
                : static_cast<Machine *>(new DryingMachine(model, powerConsumption, serialNumber, value));
        } catch (InvalidSerialNumberFormatException &e) {
            e.print();
            n--;
            i--;
        }
    }

    return machines;
}

void cleanUp(Machine **machines, int n) {
    for (int i = 0; i < n; i++) {
        delete machines[i];
    }
    delete[] machines;
}

void calculatePercentageOfCost(Machine **machines, int n) {
    //pass
}

int main() {
    int testCase, n;
    cin >> testCase;

    switch (testCase) {
        case 1: {
            cout << "TESTING ABSTRACT CLASS AND CHILD CLASSES" << endl;
            cin >> n;
            Machine **machines = createMachines(n);
            for (int i = 0; i < n; i++) {
                machines[i]->showDetails();
            }
            cleanUp(machines, n);
            cout << "ABSTRACT CLASS AND CHILD CLASSES OK" << endl;
            break;
        }
        case 2: {
            cout << "TEST EXCEPTION HANDLING" << endl;
            cin >> n;
            Machine **machines = createMachines(n);
            for (int i = 0; i < n; i++) {
                machines[i]->showDetails();
            }
            cleanUp(machines, n);
            cout << "EXCEPTION HANDLING OK" << endl;
            break;
        }
        default: {
            cout << "INTEGRATION TEST AND TESTING GLOBAL FUNCTION" << endl;
            cin >> n;
            Machine **machines = createMachines(n);
            for (int i = 0; i < n; i++) {
                machines[i]->showDetails();
            }
            calculatePercentageOfCost(machines, n);
            cleanUp(machines, n);
            cout << "INTEGRATION TEST AND TESTING GLOBAL FUNCTION OK" << endl;
            break;
        }
    }
    return 0;
}
*/