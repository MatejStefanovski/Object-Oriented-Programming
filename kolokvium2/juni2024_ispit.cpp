#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Song {
private:
    string naslov;
    string ime;
    string izveduvac;
    int vremetraenje;
public:
    Song(string naslov="", string ime="", string izveduvac="", int vremetraenje=0) {
        this->naslov=naslov;
        this->ime=ime;
        this->izveduvac=izveduvac;
        this->vremetraenje=vremetraenje;
    }
    Song(const Song& song) {
        this->naslov=song.naslov;
        this->ime=song.ime;
        this->izveduvac=song.izveduvac;
        this->vremetraenje=song.vremetraenje;
    }
    friend ifstream& operator>>(ifstream& in, Song& song) {
        getline(in,song.naslov);
        getline(in,song.ime);
        getline(in,song.izveduvac);
        in>>song.vremetraenje;
        in.ignore();
        return in;
    }
    void print (ofstream& out) {
        out << "Song title: " << naslov << ", Author: " << ime << ", Interpreted by: " << izveduvac << ", " << vremetraenje << " sek." << endl;
    }
    bool isti(const Song& s) {
        if (this->naslov == s.naslov && this->ime == s.ime && this->izveduvac == s.izveduvac && this->vremetraenje == s.vremetraenje) {
            return true;
        }
        return false;
    }
    void setNaslov(string naslov) {
        this->naslov=naslov;
    }
    void setIme(string ime) {
        this->ime=ime;
    }
    void setizveduvac(string izveduvac) {
        this->izveduvac=izveduvac;
    }
    void setVremetraenje(int vremetraenje) {
        this->vremetraenje=vremetraenje;
    }
    string getNaslov() {
        return this->naslov;
    }
    string getIme() {
        return this->ime;
    }
    string getizveduvac() {
        return this->izveduvac;
    }
    int getVremetraenje() {
        return this->vremetraenje;
    }
};

class Festival {
private:
    string ime;
    string grad;
    string datum;
    Song *songs;
    int n;
public:
    Festival(string ime="", string grad="", string datum="", Song *songs=nullptr, int n=0) {
        this->ime=ime;
        this->grad=grad;
        this->datum=datum;
        this->n=n;
        this->songs=new Song[n];
        for (int i = 0; i < n; i++) {
            this->songs[i] = songs[i];
        }
    }
    Festival(const Festival& f) {
        this->ime=f.ime;
        this->grad=f.grad;
        this->datum=f.datum;
        this->n=f.n;
        this->songs=new Song[f.n];
        for (int i = 0; i < f.n; i++) {
            this->songs[i] = f.songs[i];
        }
    }
    ~Festival() {
        delete[] songs;
    }
    Festival &operator-=(const Song& s) {
        if (n==0) {
            cout << "Trying to delete from an empty list!" << endl;
            return *this;
        }
        int count=0;
        for(int i=0; i<n; i++) {
            if (songs[i].isti(s)) {
                count++;
            }
        }
        if (count==0) {
            return *this;
        }
        Song *temp=new Song[n-count];
        int j=0;
        for(int i=0; i<n; i++) {
            if (!songs[i].isti(s)) {
                temp[j]=songs[i];
                j++;
            }
        }
        delete[] songs;
        songs=temp;
        n-=count;
        return *this;
    }
    void print(ofstream& out) {
        out << "Festival: " << ime << " - " << grad << ", " << datum << endl;
        if (n==0) {
            return;
        }
        for (int i = 0; i < n; ++i) {
            songs[i].print(out);
        }
    }
    friend istream &operator>>(ifstream& in, Festival& f) {
        getline(in, f.ime);
        getline(in, f.grad);
        getline(in, f.datum);
        in>>f.n;
        in.ignore();
        f.songs=new Song[f.n];
        for (int i = 0; i < f.n; i++) {
            in>>f.songs[i];
        }
        return in;
    }
    Festival notFromAuthor(string author) const {
        int count=0;
        for(int i=0; i<n; i++) {
            if (songs[i].getIme()!=author) {
                count++;
            }
        }
        int j=0;
        Song *temp=new Song[count];
        for (int i = 0; i < n; i++) {
            if (songs[i].getIme()!=author) {
                temp[j]=songs[i];
                j++;
            }
        }
        return Festival(ime, grad, datum, temp, count);
    }
};

void wtf() {
    ofstream fout("vlezna.txt");
    string line;
    while (getline(cin, line)) {
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

    Festival festival;
    ifstream fin("vlezna.txt");
    fin >> festival;
    fin.close();

    string author;
    getline(cin, author);

    Song song(author, author, author, 0);
    festival-=song;

    ofstream out1("izlezna1.txt");
    festival.print(out1);
    out1.close();

    Festival filtered = festival.notFromAuthor(author);
    ofstream out2("izlezna2.txt");
    filtered.print(out2);
    out2.close();

    cout << "All the data for the festival:" << endl;
    rff("izlezna1.txt");
    cout << "Songs NOT from the author " << author << ": " << endl;
    rff("izlezna2.txt");


    return 0;
}




/*
 *#include <iostream>
#include <string>

using namespace std;

class InvalidCodeFormatException {
private:
    string kod;
public:
    InvalidCodeFormatException(string k) {
        kod = k;
    }
    void print() {
        cout << "The code " << kod << " is invalid doctor code format. THE CODE MUST BE 8 CHARACTERS LONG AND CANNOT CONTAIN COMMA." << endl;
    }
};

class Doctor {
protected:
    string ime;
    string prezime;
    float plata;
    string kod;
public:
    Doctor(string ime="", string prezime="", string kod="") {
        if (kod.size()!=8) {
            throw InvalidCodeFormatException(kod);
        }
        int zapirki=0;
        for (int i=0; i<8; i++) {
            if (kod[i]==',') {
                zapirki++;
            }
        }
        if (zapirki>0) {
            throw InvalidCodeFormatException(kod);
        }
        this->ime = ime;
        this->prezime = prezime;
        this->kod = kod;
        this->plata = 0;
    }
    Doctor(const Doctor &doctor) {
        this->ime = doctor.ime;
        this->prezime = doctor.prezime;
        this->kod = doctor.kod;
        this->plata = doctor.plata;
    }
    virtual float calculateSalary()=0;
    virtual void print()=0;
};

class GeneralDoctor : public Doctor {
private:
    int br;
public:
    GeneralDoctor():Doctor() {
        this->br = 0;
    }
    GeneralDoctor(string ime, string prezime, string kod, int br):Doctor(ime, prezime, kod) {
        this->br = br;
    }
    GeneralDoctor(const GeneralDoctor &doctor):Doctor(doctor) {
        this->br = doctor.br;
    }
    float calculateSalary() override {
        int plata=45000+((br/10)*3000);
        return plata-plata*0.07;
    }
    void print() override {
        cout << "General Doctor: " << ime << " " << prezime << " CODE:" << kod << " Salary: " << calculateSalary() << endl;
    }
};

class Specialist : public Doctor {
private:
    string specijalnost;
    int intervencii;
    int iskustvo;
public:
    Specialist():Doctor() {
        this->iskustvo = 0;
        this->specijalnost = "";
        this->intervencii = 0;
    }
    Specialist(string ime, string prezime, string kod, string specijalnost, int intervencii, int iskustvo) : Doctor(ime, prezime, kod) {
        this->iskustvo = iskustvo;
        this->specijalnost = specijalnost;
        this->intervencii = intervencii;
    }
    Specialist(const Specialist &doctor):Doctor(doctor) {
        this->iskustvo = doctor.iskustvo;
        this->specijalnost = doctor.specijalnost;
        this->intervencii = doctor.intervencii;
    }
    float calculateSalary() override {
        float p=55000;
        float t=iskustvo*5;
        p=p+(t*p)/100;
        p+=intervencii*85;
        p-=0.07*p;
        return p;
    }
    void print() override {
        cout << "Specialist: " << ime << " " << prezime << " CODE:" << kod << " " << specijalnost << " Salary: " << calculateSalary() << endl;
    }
};

void findDoctorsPercentage(Doctor **doctors, int n) {
    int br_spec=0, br_mat=0, nn=0;
    for (int i=0; i<n; i++) {
        if (doctors[i]) {
            nn++;
            if (dynamic_cast<GeneralDoctor*>(doctors[i])) {
                br_mat++;
            }
            else if (dynamic_cast<Specialist*>(doctors[i])) {
                br_spec++;
            }
        }
    }
    cout << 100.0*br_spec/nn << "% of the doctors are specialists and " << 100.0*br_mat/nn << "% are general doctors." << endl;
}

int main()
{
    int testCase, n;
    string name, surname, specialty, code;
    int numberOfPatients, yearsOfExperience, numberOfInterventions;
    cin >> testCase;

    if (testCase == 1)
    {
        cout << "TESTING GENERAL DOCTOR CLASS" << endl;
            Doctor *d = new GeneralDoctor("John", "Smith", "236XY@2B", 120);
            Doctor *d1 = new GeneralDoctor("Marco", "Brown", "345X!Y2B", 120);
            Doctor *d2 = new GeneralDoctor("Emily", "Johnson", "ABCD123@", 230);
            d->print();
            d1->print();
            d2->print();

        cout << "GENERAL DOCTOR CLASS OK!" << endl;
    }
    else if (testCase == 2)
    {
        cout << "TESTING SPECIALIST DOCTOR CLASS" << endl;
            Doctor *d = new Specialist("Beth", "Davis", "96Tr$$33", "Cardiologist", 45, 5);
            Doctor *d1 = new Specialist("William", "Wilson", "785#Qy2B", "Pulmonologist", 50, 7);
            Doctor *d2 = new Specialist("Micheal", "Rosen", "7896YZ$s", "Radiologist", 41, 10);
            d->print();
            d1->print();
            d2->print();
        cout << "SPECIALIST DOCTOR CLASS OK!" << endl;
    }
    else if (testCase == 3)
    {
        cout << "TESTING EXCEPTION HANDLING" << endl;
        try {
            Doctor *d = new GeneralDoctor("John", "Smith", "23Y@2B", 120);
            d->print();
            delete d;
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }
        cout << "EXCEPTION HANDLING OK!" << endl;
    }
    else if (testCase == 4)
    {
        cout << "TESTING EXCEPTION HANDLING" << endl;
        try {
            Doctor *d = new Specialist("Beth", "Davis", "9,R$$334", "Cardiologist", 45, 5);
            d->print();
            delete d;
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }
        cout << "EXCEPTION HANDLING OK!" << endl;
    }
    else if (testCase == 5)
    {
        cout << "TESTING EXCEPTION HANDLING" << endl;
        try {
            Doctor *d = new Specialist("Beth", "Davis", "9,R$$334", "Cardiologist", 45, 5);
            d->print();
            delete d;
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }

        try {
            Doctor *d1 = new Specialist("William", "Wilson", "785#Qy2B", "Pulmonologist", 50, 7);
            d1->print();
            delete d1;
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }

        try {
            Doctor *d2 = new Specialist("Beth", "Davis", "96Tr,", "Cardiologist", 45, 5);
            d2->print();
            delete d2;
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }

        cout << "EXCEPTION HANDLING OK!" << endl;
    }
    else
    {
        cout << "INTEGRATION TEST AND TESTING GLOBAL FUNCTION!" << endl;
        cin >> n;
        Doctor **doctors = new Doctor *[n];
        for (int i = 0; i < n; i++)
        {
            int t;
            cin >> t;
            cin >> name >> surname;
            cin >> code;
            try {
                if (t == 1) // General doctor
                {
                    cin >> numberOfPatients;

                    doctors[i] = new GeneralDoctor(name, surname, code, numberOfPatients);

                }
                else // Specialist
                {
                    cin >> specialty;
                    cin >> numberOfInterventions >> yearsOfExperience;

                    doctors[i] = new Specialist(name, surname, code, specialty, numberOfInterventions, yearsOfExperience);

                }
            }
            catch (InvalidCodeFormatException &e) {
                e.print();
                doctors[i]=nullptr;
            }
        }
        cout << "LIST OF ALL DOCTORS: " << endl;
        for (int i = 0; i < n; i++)
        {
            if (doctors[i])
                doctors[i]->print();
        }
        findDoctorsPercentage(doctors, n);
        for (int i = 0; i < n; i++)
        {
            delete doctors[i];
        }
        delete[] doctors;
    }
    return 0;
}
*/