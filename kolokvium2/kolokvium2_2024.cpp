#include <iostream>
#include <string>

using namespace std;

class Library {
protected:
    string name;
    string grad;
    double cena;
    bool vikend;
public:
    Library(string name="", string grad="", double cena=0, bool vikend=false) {
        this->name = name;
        this->grad = grad;
        this->cena = cena;
        this->vikend = vikend;
    }
    Library(const Library& library) {
        this->name = library.name;
        this->grad = library.grad;
        this->cena = library.cena;
        this->vikend = library.vikend;
    }
    bool get_vikend() {
        return vikend;
    }
    virtual void printDetail()=0;
    virtual double calculateMembershipCardCost()=0;
};

class AcademicLibrary:public Library {
private:
    bool istrazuvanje;
    int br_kolekcii;
public:
    AcademicLibrary():Library() {
        istrazuvanje = false;
        br_kolekcii = 0;
    }
    AcademicLibrary(string name, string grad, double cena, bool vikend, bool istrazuvanje, int br_kolekcii):Library(name, grad, cena, vikend) {
        this->istrazuvanje = istrazuvanje;
        this->br_kolekcii = br_kolekcii;
    }
    AcademicLibrary(const AcademicLibrary& library):Library(library) {
        this->istrazuvanje = library.istrazuvanje;
        this->br_kolekcii = library.br_kolekcii;
    }
    double calculateMembershipCardCost() override {
        double cena1=cena;
        if (istrazuvanje) {
            cena1 = cena1 + cena1*0.24;
        }
        return cena1+br_kolekcii*6;
    }
    void printDetail() override{
        cout << name << " - " << "(Academic) " << grad << " " << br_kolekcii << " " << calculateMembershipCardCost() << endl;
    }
};

class NationalLibrary:public Library {
private:
    bool k_nasledstvo;
    int rakopisi;
public:
    NationalLibrary():Library() {
        k_nasledstvo = false;
        rakopisi = 0;
    }
    NationalLibrary(string name, string grad, double cena, bool vikend, bool k_nasledstvo, int rakopisi):Library(name, grad, cena, vikend) {
        this->k_nasledstvo = k_nasledstvo;
        this->rakopisi = rakopisi;
    }
    NationalLibrary(const NationalLibrary& library):Library(library) {
        this->k_nasledstvo = library.k_nasledstvo;
        this->rakopisi = library.rakopisi;
    }
    double calculateMembershipCardCost() override {
        double cena1=cena;
        if (k_nasledstvo) {
            cena1 = cena1 - cena1*0.07;
        }
        return cena1+rakopisi*15;
    }
    void printDetail() override{
        cout << name << " - " << "(National) " << grad << " " << rakopisi << " " << calculateMembershipCardCost() << endl;
    }
};

int findMostExpensiveNationalLibrary(Library **l, int n) {
    int index=-1;
    double max_cena=0;
    for (int i=0; i<n; i++) {
        if (dynamic_cast<NationalLibrary*>(l[i])) {
            double currentCena = l[i]->calculateMembershipCardCost();
            if (currentCena > max_cena) {
                max_cena = currentCena;
                index = i;
            }
            else if (currentCena == max_cena && l[i]->get_vikend()) {
                index = i;
            }
        }
    }
    return index;
}

int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Library** m = new Library*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        bool weekend_working;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> weekend_working;
        cin.ignore();

        if (type == 1) {
            bool open_cooperation;
            int specialized_articles;

            cin >> open_cooperation >> specialized_articles;
            cin.ignore();

            m[i] = new AcademicLibrary(name, city, base_price, weekend_working, open_cooperation, specialized_articles);
        } else {
            bool cultural_program;
            int national_articles;

            cin >> cultural_program >> national_articles;
            cin.ignore();

            m[i] = new NationalLibrary(name, city, base_price, weekend_working, cultural_program, national_articles);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateMembershipCardCost() << endl;
        }
        cout << "calculateMembershipCardCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    }
    else if(testCase == 4){
        int most_expensive_nat_lib_index = findMostExpensiveNationalLibrary(m, n);
        if(most_expensive_nat_lib_index>=0){
            m[most_expensive_nat_lib_index]->printDetail();
        }else{
            cout << "National Library not found in the array!"<<endl;
        }
        cout << "findMostExpensiveNationalLibrary method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}


/*
 *#include <iostream>
#include <cstring>

using namespace std;

class Museum {
protected:
    string ime;
    string grad;
    double cena;
    int br_casovi;
public:
    Museum(string ime="", string grad="", double cena=0, int br_casovi=0) {
        this->ime=ime;
        this->grad=grad;
        this->cena=cena;
        this->br_casovi=br_casovi;
    }
    Museum(const Museum &m) {
        this->ime=m.ime;
        this->grad=m.grad;
        this->cena=m.cena;
        this->br_casovi=m.br_casovi;
    }
    double get_cena() {
        return cena;
    }
    int get_casovi() {
        return br_casovi;
    }
    virtual void printDetails()=0;
    virtual double calculateTicketCost()=0;
};

class ScientificMuseum : public Museum {
private:
    bool ramki;
    int prezentacii;
public:
    ScientificMuseum():Museum() {
        ramki=false;
        prezentacii=0;
    }
    ScientificMuseum(string ime, string grad, double cena, int br_casovi, bool ramki, int prezentaii):Museum(ime, grad, cena, br_casovi) {
        this->ramki=ramki;
        this->prezentacii=prezentaii;
    }
    ScientificMuseum(const ScientificMuseum &m):Museum(m) {
        this->ramki=m.ramki;
        this->prezentacii=m.prezentacii;
    }
    double calculateTicketCost() {
        double kraj_cena=cena;
        if (ramki) {
            kraj_cena=kraj_cena+kraj_cena*0.12;
        }
        return kraj_cena+prezentacii*6;
    }
    void printDetails() {
        cout << ime << " - (Scientific) " << grad << " " << prezentacii << " " << calculateTicketCost() << endl;
    }
};

class ArtMuseum : public Museum {
private:
    bool izlozbi;
    int umetnicki_dela;
public:
    ArtMuseum():Museum() {
        izlozbi=false;
        umetnicki_dela=0;
    }
    ArtMuseum(string ime, string grad, double cena, int br_casovi, bool izlozbi, int umetnicki_dela):Museum(ime, grad, cena, br_casovi) {
        this->izlozbi=izlozbi;
        this->umetnicki_dela=umetnicki_dela;
    }
    ArtMuseum(const ArtMuseum &m):Museum(m) {
        this->izlozbi=m.izlozbi;
        this->umetnicki_dela=m.umetnicki_dela;
    }
    double calculateTicketCost() {
        double kraj_cena=cena;
        if (izlozbi) {
            kraj_cena=kraj_cena-kraj_cena*0.18;
        }
        return kraj_cena+umetnicki_dela*3;
    }
    void printDetails() {
        cout << ime << " - (Art) " << grad << " " << izlozbi << " " << calculateTicketCost() << endl;
    }
};

int findCheapestScientificMuseum(Museum **m, int n) {
    int index=-1, casovi=0;
    double min_cena=m[0]->get_cena();
    for (int i=0; i<n; i++) {
        if (dynamic_cast<ScientificMuseum*>(m[i])) {
            if (m[i]->get_cena()<min_cena) {
                min_cena=m[i]->get_cena();
                index=i;
                casovi=m[i]->get_casovi();
            }
            else if (m[i]->get_cena()==min_cena) {
                if (m[i]->get_casovi()>casovi) {
                    min_cena=m[i]->get_cena();
                    index=i;
                    casovi=m[i]->get_casovi();
                }
            }
        }
    }
    return index;
}

int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Museum** m = new Museum*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        int working_hours;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> working_hours;
        cin.ignore();

        if (type == 1) {
            bool interactive_shows;
            int multimedia_pres;

            cin >> interactive_shows >> multimedia_pres;
            cin.ignore();

            m[i] = new ScientificMuseum(name, city, base_price, working_hours, interactive_shows, multimedia_pres);
        } else {
            bool amateur_shows;
            int original_artwork;

            cin >> amateur_shows >> original_artwork;
            cin.ignore();

            m[i] = new ArtMuseum(name, city, base_price, working_hours, amateur_shows, original_artwork);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateTicketCost() << endl;
        }
        cout << "calculateTicketCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetails();
        }
        cout << "printDetail method OK" << endl;
    }
    else if(testCase == 4){
        int cheapest_sci_museum_index = findCheapestScientificMuseum(m, n);
        if(cheapest_sci_museum_index>=0){
            m[cheapest_sci_museum_index]->printDetails();
        }else{
            cout << "Scientific Museum not found in the array!"<<endl;
        }
        cout << "findCheapestOnlineOrder method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}
*/


/*#include <iostream>
#include <cstring>
#include <fstream>
#include <stdexcept>

using namespace std;

class NoProductFoundException : public exception {
    string msg;
public:
    NoProductFoundException(const string& category) {
        msg = "No products from category " + category + " were found in the store";
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

class Product {
protected:
    string name;
    string category;
    int price;
    int quantity;
public:
    Product() : name(""), category(""), price(0), quantity(0) {}
    Product(string name, string category, int price, int quantity): name(name), category(category), price(price), quantity(quantity) {}
    Product(const Product &product) : name(product.name), category(product.category), price(product.price), quantity(product.quantity) {}

    int totalPrice() const {
        return price * quantity;
    }

    string get_category() const {
        return category;
    }

    friend ostream& operator<<(ostream& os, const Product &product) {
        os << product.name << " (" << product.category << ") " << product.price << " x " << product.quantity << " = " << product.totalPrice();
        return os;
    }
};

class Store {
private:
    Product *products;
    int n;
public:
    Store() : products(nullptr), n(0) {}

    Store(Product *products, int n) {
        this->n = n;
        this->products = new Product[n];
        for (int i = 0; i < n; i++) {
            this->products[i] = products[i];
        }
    }

    Store(const Store& other) {
        n = other.n;
        products = new Product[n];
        for (int i = 0; i < n; i++) {
            products[i] = other.products[i];
        }
    }

    ~Store() {
        delete[] products;
    }

    Store& operator=(const Store& other) {
        if (this != &other) {
            delete[] products;
            n = other.n;
            products = new Product[n];
            for (int i = 0; i < n; i++) {
                products[i] = other.products[i];
            }
        }
        return *this;
    }

    Store& operator+=(const Product &product) {
        Product *tmp = new Product[n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = products[i];
        }
        tmp[n] = product;
        delete[] products;
        products = tmp;
        n++;
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Store& store) {
        for (int i = 0; i < store.n; i++) {
            os << store.products[i] << endl;
        }
        return os;
    }

    Store fromCategory(const string &category) {
        Store filtered;
        for (int i = 0; i < n; i++) {
            if (products[i].get_category() == category) {
                filtered += products[i];
            }
        }
        if (filtered.n == 0) {
            throw NoProductFoundException(category);
        }
        return filtered;
    }
};

void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(cin, line)) {
        if (line == "----") break;
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

    Store s;

    ifstream fin("input.txt");
    string name, category;
    int price, quantity;
    while (getline(fin, name)) {
        if (!getline(fin, category)) break;
        if (!(fin >> quantity)) break;
        if (!(fin >> price)) break;
        fin.ignore();
        Product p(name, category, price, quantity);
        s += p;
    }

    ofstream out1("output1.txt");
    out1 << s;
    out1.close();

    string categoryFilter;
    cin >> categoryFilter;

    try {
        Store filtered = s.fromCategory(categoryFilter);
        ofstream out2("output2.txt");
        out2 << filtered;
        out2.close();
    } catch (const NoProductFoundException &e) {
        cout << e.what() << endl;
        ofstream out2("output2.txt");
        out2.close(); // Create empty file
    }

    cout << "All products:" << endl;
    rff("output1.txt");
    cout << "Products from category " << categoryFilter << ": " << endl;
    rff("output2.txt");

    return 0;
}
*/


/*#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;

class StudentFailedException {
private:
    string indeks;
public:
    StudentFailedException(string indeks) {
        this->indeks = indeks;
    }
    void print() {
        cout << "Student with id " << indeks << " failed the course" << endl;
    }
};

class Student {
private:
    string indeks;
    string ime;
    string prezime;
    int poeni;
public:
    Student(string indeks="", string ime="", string prezime="", int poeni=0) {
        this->indeks = indeks;
        this->ime = ime;
        this->prezime = prezime;
        this->poeni = poeni;
    }
    Student(const Student& student) {
        this->indeks = student.indeks;
        this->ime = student.ime;
        this->prezime = student.prezime;
        this->poeni = student.poeni;
    }
    string getIndeks() {
        return indeks;
    }
    int grade() {
        if (poeni<50) {
            return 5;
        }
        else if (poeni<60) {
            return 6;
        }
        else if (poeni<70) {
            return 7;
        }
        else if (poeni<80) {
            return 8;
        }
        else if (poeni<90) {
            return 9;
        }
        else {
            return 10;
        }
    }
    friend ostream& operator<<(ostream& os, Student& student) {
        os << student.indeks << " " << student.ime << " " << student.prezime << " " << student.poeni << " Grade: " << student.grade();
        return os;
    }
};

class Results {
private:
    Student *niza;
    int n;
public:
    Results(Student *niza=nullptr, int n=0) {
        this->n=n;
        this->niza=new Student[n];
        for (int i=0; i<n; i++) {
            this->niza[i]=niza[i];
        }
    }
    Results(const Results& student) {
        this->n=student.n;
        this->niza=new Student[student.n];
        for (int i=0; i<n; i++) {
            this->niza[i]=student.niza[i];
        }
    }
    ~Results() {
        delete [] niza;
    }
    Results& operator=(const Results& other) {
        if (this != &other) {
            delete[] niza;
            n = other.n;
            niza = new Student[n];
            for (int i = 0; i < n; i++) {
                niza[i] = other.niza[i];
            }
        }
        return *this;
    }
    Results& operator+=(Student &s) {
        if (s.grade()==5) {
            throw StudentFailedException(s.getIndeks());
            return *this;
        }
        Student *tmp=new Student[n+1];
        for (int i=0; i<n; i++) {
            tmp[i]=niza[i];
        }
        tmp[n]=s;
        n++;
        delete [] niza;
        niza=tmp;
        return *this;
    }
    friend ostream& operator<<(ostream& os, Results& student) {
        if (student.n==0){
            os << "None" << endl;
            return os;
        }
        for (int i=0; i<student.n; i++) {
            os << student.niza[i] << endl;
        }
        return os;
    }
    Results withGrade(int grade) {
        int j=0, count=0;
        for (int i=0; i<n; i++) {
            if (niza[i].grade()==grade) {
                count++;
            }
        }
        Student *tmp=new Student[count];
        for (int i=0; i<n; i++) {
            if (niza[i].grade()==grade) {
                tmp[j]=niza[i];
                j++;
            }
        }
        Results results1(tmp, count);
        return results1;
    }
};

void wtf() {
    ofstream fout("input.txt");
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

    Results results;

    ifstream fin("input.txt");
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string indeks, ime, prezime;
        int poeni;
        ss >> indeks >> ime >> prezime >> poeni;

        Student s(indeks, ime, prezime, poeni);
        try {
            results += s;
        } catch (StudentFailedException &e) {
            e.print();
        }
    }

    ofstream fout("output1.txt");
    fout << results;
    fout.close();

    int grade;
    cin >> grade;

    Results filtered = results.withGrade(grade);
    ofstream fout2("output2.txt");
    fout2 << filtered;
    fout2.close();

    cout << "All students:" << endl;
    rff("output1.txt");
    cout << "Grade report for grade " << grade << ":" << endl;
    rff("output2.txt");

    return 0;
}
*/