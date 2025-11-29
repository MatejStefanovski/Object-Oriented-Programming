#include <iostream>
#include <cstring>

using namespace std;

class HotelReservation {
protected:
    int denovi;
    int broj_lica;
    string ime;
    string prezime;
public:
    HotelReservation(int denovi, int broj_lica, string ime, string prezime) {
        this->denovi=denovi;
        this->broj_lica=broj_lica;
        this->ime=ime;
        this->prezime=prezime;
    }
    virtual int price() {
        return denovi*broj_lica*25;
    }
    virtual int price(int amount) {
        if (amount >= price())
            return amount - price();
        else {
            cout << "Za vashata rezervacija treba da naplatite " << price() << endl;
            return -1;
        }
    }
};

class HalfBoardHotelReservation:public HotelReservation {
public:
    HalfBoardHotelReservation(int denovi, int broj_lica, string ime, string prezime):HotelReservation
    (denovi, broj_lica, ime, prezime) {}
    int price(int amount) {
        int cena = HotelReservation::price() + broj_lica * 5;
        if (amount >= cena)
            return amount - cena;
        else {
            cout << "Za vashata rezervacija treba da naplatite " << cena << endl;
            return -1;
        }
    }
};

class Hotel{
private:
    string ime;
    int saldo;
public:
    Hotel(string ime) {
        this->ime = ime;
        saldo = 0;
    }
    int pay(HotelReservation &hr, int uplata) {
        int kusur = hr.price(uplata);
        if (kusur != -1)
            saldo += uplata - kusur;
        return kusur;
    }
};

int main() {

    return 0;
}
