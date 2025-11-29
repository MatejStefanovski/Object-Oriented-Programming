#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class InvalidCodeFormatException {
private:
    string kod;
public:
    InvalidCodeFormatException(string kod) {
        this->kod=kod;
    }
    void print() {
        cout << "The code " << kod << " is invalid doctor code format. THE CODE MUST BE 8 CHARACTERS LONG AND CANNOT CONTAIN COMMA." << endl;
    }
};

class Doctor {
protected:
    string ime;
    string prezime;
    double plata;
    string kod;
public:
    Doctor(string ime="", string prezime="", string kod="", double plata=0.0) {
        int zapirki=0;
        for (int i=0; i<kod.length(); i++) {
            if (kod[i]==',') {
                zapirki++;
            }
        }
        if (kod.length()!=8 || zapirki>0) {
            throw InvalidCodeFormatException(kod);
        }
        this->ime=ime;
        this->prezime=prezime;
        this->plata=plata;
        this->kod=kod;
    }
    Doctor(const Doctor& d) {
        this->ime=d.ime;
        this->prezime=d.prezime;
        this->plata=d.plata;
        this->kod=d.kod;
    }
    virtual float calculateSalary()=0;
    virtual void print()=0;
};

class GeneralDoctor:public Doctor {
private:
    int pacienti;
public:
    GeneralDoctor(string ime="", string prezime="", string kod="", int pacienti=0):Doctor(ime, prezime, kod) {
        this->pacienti=pacienti;
    }
    GeneralDoctor(const GeneralDoctor& g):Doctor(g) {
        this->pacienti=g.pacienti;
    }
    float calculateSalary() override {
        float os=45000;
        return (os+(3000.0*pacienti/10))*0.93;
    }
    void print() override {
        cout << "General Doctor: " << ime << " " << prezime << " CODE:" << kod << " Salary: " << calculateSalary() << endl;
    }
};

class Specialist:public Doctor {
private:
    string specijalnost;
    int intervencii;
    int iskustvo;
public:
    Specialist(string ime="", string prezime="", string kod="", string specijalnost="", int intervencii=0, int iskustvo=0):Doctor(ime, prezime, kod) {
        this->specijalnost=specijalnost;
        this->intervencii=intervencii;
        this->iskustvo=iskustvo;
    }
    Specialist(const Specialist& s):Doctor(s) {
        this->specijalnost=s.specijalnost;
        this->intervencii=s.intervencii;
        this->iskustvo=s.iskustvo;
    }
    float calculateSalary() override {
        float os=55000;
        int d=85*intervencii;
        int procent=5*iskustvo;
        float kraj=os+(procent*1.0/100)*os+d;
        return kraj*0.93;
    }
    void print() override {
        cout << "Specialist: " << ime << " " << prezime << " CODE:" << kod << " " << specijalnost << " Salary: " << calculateSalary() << endl;
    }
};

void findDoctorsPercentage(Doctor **doctors, int n) {
    int specijalist=0;
    int general=0, valid=0;
    for (int i=0; i<n; i++) {
        if (doctors[i]) {
            if (dynamic_cast<GeneralDoctor*>(doctors[i])) {
                general++;
            }
            else if (dynamic_cast<Specialist*>(doctors[i])) {
                specijalist++;
            }
            valid++;
        }
    }
    cout << 100.0*(specijalist*1.0/valid) << "% of the doctors are specialists and " << 100.0*(general*1.0/valid) << "% are general doctors." << endl;
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
        }
        catch (InvalidCodeFormatException &e) {
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
        }
        catch (InvalidCodeFormatException &e) {
            e.print();
        }
        cout << "EXCEPTION HANDLING OK!" << endl;
    }
    else if (testCase == 5)
    {
        cout << "TESTING EXCEPTION HANDLING" << endl;
        try{
            Doctor *d = new Specialist("Beth", "Davis", "9,R$$334", "Cardiologist", 45, 5);
            d->print();
        }
        catch (InvalidCodeFormatException &e) {
            e.print();
        }

        try{
            Doctor *d1 = new Specialist("William", "Wilson", "785#Qy2B", "Pulmonologist", 50, 7);
            d1->print();
        }
        catch (InvalidCodeFormatException &e) {
            e.print();
        }

        try{
            Doctor *d2 = new Specialist("Beth", "Davis", "96Tr,", "Cardiologist", 45, 5);
            d2->print();
        }
        catch (InvalidCodeFormatException &e) {
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
            try{
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
            if (doctors[i] != nullptr)
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
