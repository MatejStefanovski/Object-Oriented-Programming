#include <iostream>
#include <cstring>

using namespace std;

class MobilePhone {
private:
    char model[20];
    int br_model;
    int godina;
public:
    MobilePhone() {
        strcpy(model,"");
        br_model = 0;
        godina = 0;
    }
    MobilePhone(char *model, int br_model, int godina) {
        strcpy(this->model,model);
        this->br_model = br_model;
        this->godina = godina;
    }
    MobilePhone(const MobilePhone &m) {
        strcpy(this->model,m.model);
        this->br_model = m.br_model;
        this->godina = m.godina;
    }
    void print() {
        cout << model << " " << br_model << " " << godina << endl;
    }
};

class Owner {
private:
    char ime[20];
    char prezime[20];
    MobilePhone telefon;
public:
    Owner() {
        strcpy(ime,"");
        strcpy(prezime,"");
    }
    Owner(char *ime, char *prezime, MobilePhone telefon) {
        strcpy(this->ime,ime);
        strcpy(this->prezime,prezime);
        this->telefon = telefon;
    }
    ~Owner(){}
    void print() {
        cout << ime << " " << prezime << " has a mobile phone" << endl;
        telefon.print();
    }
};

int main() {
    MobilePhone telefon("Samsung", 23, 2023);
    Owner owner("Matej", "Stefanovski", telefon);
    owner.print();
    return 0;
}


/*#include <iostream>
#include <cstring>

using namespace std;

class Date {
private:
    int year;
    int month;
    int day;
public:
    Date() {
        year = 0;
        month = 0;
        day = 0;
    }
    Date(int year, int month, int day) {
        this->year = year;
        this->month = month;
        this->day = day;
    }
    void print() {
        cout << year << "." << month << "." << day << endl;
    }
};

class Person {
private:
    char ime[20];
    char prezime[20];
public:
    Person() {
        strcpy(ime, "");
        strcpy(prezime, "");
    }
    Person(char ime[], char prezime[]) {
        strcpy(this->ime, ime);
        strcpy(this->prezime, prezime);
    }
    void print() {
        cout << ime << " " << prezime << endl;
    }
};

class Car {
private:
    Person p;
    Date d;
    char model[20];
public:
    Car() {
        strcpy(model, "");
    }
    Car(Person p, Date d, char *model) {
        this->p = p;
        this->d = d;
        strcpy(this->model, model);
    }
    void print() {
        p.print();
        d.print();
        cout << model << endl;
    }
};

int main() {
    Person p("Matej", "Stefanovski");
    Date d(2021, 12, 29);
    Car c(p, d, "Ferrari");
    c.print();
    return 0;
}
*/


/*#include <iostream>
#include <cstring>

using namespace std;

class Flight {
private:
    char ime[20];
    char arrival[20];
    char departure[20];
    int cena;
public:
    Flight() {
        strcpy(ime,"");
        strcpy(arrival,"");
        strcpy(departure,"");
        cena = 0;
    }
    Flight(char ime[], char arrival[], char departure[], int cena) {
        strcpy(this->ime,ime);
        strcpy(this->arrival,arrival);
        strcpy(this->departure,departure);
        this->cena = cena;
    }
    Flight(const Flight &flight) {
        strcpy(this->ime,flight.ime);
        strcpy(this->arrival,flight.arrival);
        strcpy(this->departure,flight.departure);
        this->cena = flight.cena;
    }
    char *getIme() {
        return ime;
    }
    char *getArrival() {
        return arrival;
    }
    char *getDeparture() {
        return departure;
    }
    int getCena() {
        return cena;
    }
};

class Airport {
private:
    char ime[20];
    int br_letovi;
    Flight flights[100];
public:
    Airport() {
        strcpy(ime,"");
        br_letovi = 0;
    }
    Airport(char ime[], int br_letovi, Flight flights[]) {
        strcpy(this->ime,ime);
        this->br_letovi = br_letovi;
        for (int i=0; i<br_letovi; i++) {
            this->flights[i] = flights[i];
        }
    }
    Flight cheapestFlight() {
        int min=flights[0].getCena();
        Flight flight=flights[0];
        for (int i=0; i<br_letovi; i++) {
            if (flights[i].getCena()<min) {
                min=flights[i].getCena();
                flight=flights[i];
            }
        }
        return flight;
    }
};

int main() {
    Flight flight[3];
    Flight f2("Ime2", "Viena", "Skopje", 5000);
    Flight f1("Ime1", "Lonodn", "Skopje", 3000);
    Flight f3("Ime3", "New York", "Skopje", 7000);
    flight[0] = f1;
    flight[1] = f2;
    flight[2] = f3;
    Airport a1("Airport1", 3, flight);
    Flight ff=a1.cheapestFlight();
    cout << ff.getIme() << " " << ff.getArrival() << " " << ff.getDeparture() << " " << ff.getCena() << endl;
    return 0;
}
*/