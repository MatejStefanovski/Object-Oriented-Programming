#include <iostream>
#include <cstring>

using namespace std;

class StockRecord {
private:
    char id[12];
    char name[50];
    float cena;
    float momentalna_cena;
    int br_akcii;

public:
    StockRecord(const char *id = "", const char *name = "", float cena = 0, int br_akcii = 0, float momentalna_cena = 0) {
        strcpy(this->id, id);
        strcpy(this->name, name);
        this->cena = cena;
        this->momentalna_cena = momentalna_cena;
        this->br_akcii = br_akcii;
    }

    void setNewPrice(double c) {
        this->momentalna_cena = c;
    }

    double value() const {
        return br_akcii * momentalna_cena;
    }

    double profit() const {
        return br_akcii * (momentalna_cena - cena);
    }

    friend ostream &operator<<(ostream &out, const StockRecord &sr) {
        out << sr.name << " " << sr.br_akcii << " " << sr.cena << " " << sr.momentalna_cena << " " << sr.profit() << endl;
        return out;
    }
};

class Client {
private:
    char ime[60];
    int id;
    StockRecord *stock;
    int br;

public:
    Client(const char *ime = "", int id = 0, StockRecord *stock = nullptr, int br = 0) {
        strcpy(this->ime, ime);
        this->id = id;
        this->br = br;
        this->stock = new StockRecord[br];
        for (int i = 0; i < br; i++) {
            this->stock[i] = stock[i];
        }
    }

    ~Client() {
        delete[] stock;
    }

    double totalValue() const {
        double zbir = 0.0;
        for (int i = 0; i < br; i++) {
            zbir += stock[i].value();
        }
        return zbir;
    }

    Client &operator+=(const StockRecord &sr) {
        StockRecord *temp = new StockRecord[br + 1];
        for (int i = 0; i < br; i++) {
            temp[i] = stock[i];
        }
        temp[br] = sr;
        delete[] stock;
        stock = temp;
        br++;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Client &c) {
        out << c.id << " " << c.totalValue() << endl;
        for (int i = 0; i < c.br; i++) {
            out << c.stock[i];
        }
        return out;
    }
};

int main() {
    int test;
    cin >> test;

    if (test == 1) {
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    } else if (test == 2) {
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> id >> company >> price >> newPrice >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    } else if (test == 3) {
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName >> clientID >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for (int i = 0; i < n; ++i) {
            cin >> companyID >> companyName >> oldPrice >> newPrice >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if (flag) {
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;
}
