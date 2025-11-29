#include <iostream>
#include <cstring>

using namespace std;

class Library;
class LibraryMember;

class Book {
private:
    char name[20];
    char author[20];
    bool availability;
    friend class Library;
    friend void checkOutBook(LibraryMember &member, Library &lib, int &index);
public:
    Book() {
        availability = false;
        strcpy(name, "");
        strcpy(author, "");
    }
    Book(char *name, char *author, bool availability) {
        strcpy(this->name, name);
        strcpy(this->author, author);
        this->availability = availability;
    }
    Book (const Book &b) {
        strcpy(this->name, b.name);
        strcpy(this->author, b.author);
        this->availability = b.availability;
    }
    ~Book() {}
};

class Library {
private:
    char name[20];
    Book books[10];
    int n;
    friend void checkOutBook(LibraryMember &member, Library &lib, int &index);
public:
    Library() {
        n = 0;
        strcpy(name, "Brakja Miladinovci");
    }
    Library(char *name, Book *books, int n) {
        strcpy(this->name, name);
        this->n = n;
        for (int i = 0; i < n; i++) {
            this->books[i] = books[i];
        }
    }
    ~Library() {}
    void addBook(Book book) {
        if (n < 10) {
            books[n]=book;
            n++;
        }
        else {
            cout << "Library is full" << endl;
        }
    }
    void print() {
        cout << "Library: " << name << endl;
        for (int i = 0; i < n; i++) {
            cout << books[i].name << " " << books[i].author << " " << books[i].availability << endl;
        }
    }
};

class LibraryMember {
private:
    char name[20];
    int id;
    friend void checkOutBook(LibraryMember &member, Library &lib, int &index);
public:
    LibraryMember() {
        strcpy(name, "");
        id=0;
    }
    LibraryMember(char * name, int id) {
        strcpy(this->name, name);
        this->id = id;
    }
};

void checkOutBook(LibraryMember &member, Library &lib, int &index) {
    if (lib.books[index].availability == true) {
        cout << member.name << " Checks " << lib.books[index].name << endl;
    }
    else {
        cout << "Book is not available"<<endl;
    }
}

int main() {
    Library l1;
    int n;
    cout << "Enter the number of books" << endl;
    cin >> n;
    char name[30], author[30];
    bool availability;
    for (int i = 0; i < n; i++) {
        cin >> name >> author >> availability;
        Book b = Book(name, author, availability);
        l1.addBook(b);
    }
    l1.print();
    LibraryMember m1("Marko", 9541);
    int index;
    cin >> index;
    checkOutBook(m1, l1, index);
    return 0;
}



/*#include <iostream>
#include <cstring>

using namespace std;

enum Tip {
    LINUX, UNIX, WINDOWS
};

class OperativenSistem {
private:
    char ime[100];
    float verzija;
    Tip t;
    float golemna;
public:
    OperativenSistem() {
        strcpy (ime, "");
        verzija = 0.0;
        t = LINUX;
        golemna = 0.0;
    }
    OperativenSistem (char ime[], float verzija, int t, float golemna) {
        strcpy (this->ime, ime);
        this->verzija = verzija;
        this->t=(Tip)t;
        this->golemna=golemna;
    }
    OperativenSistem(const OperativenSistem &o) {
        strcpy (this->ime, o.ime);
        this->verzija = o.verzija;
        this->t=(Tip)o.t;
        this->golemna=o.golemna;
    }
    ~OperativenSistem() {
        cout<<"=====Brishenje na operativen sistem=====" << endl;
    }
    OperativenSistem &operator=(const OperativenSistem &o) {
        strcpy (this->ime, o.ime);
        this->verzija = o.verzija;
        this->t=(Tip)o.t;
        this->golemna=o.golemna;
        return *this;
    }
    void pecati() {
        cout << "Ime: " << ime << " Verzija: " << verzija << " Tip: " << t << " Golemna: " << golemna << endl;
    }
    bool ednakviSe(const OperativenSistem &os) {
        if (strcmp(ime, os.ime) == 0 && verzija == os.verzija && t == os.t && golemna == os.golemna) {
            return true;
        }
        return false;
    }
    int sporediVerzija(const OperativenSistem &os) {
        if (verzija==os.verzija) {
            return 0;
        }
        else if(verzija<os.verzija) {
            return -1;
        }
        else {
            return 1;
        }
    }
    bool istaFamilija(const OperativenSistem &sporedba) {
        if (verzija==sporedba.verzija && strcmp(ime, sporedba.ime) == 0) {
            return true;
        }
        else {
            return false;
        }
    }
    float get_verzija() {
        return verzija;
    }
};

class Repozitorium {
private:
    char ime[100];
    OperativenSistem os[100];
    int n;
public:
    Repozitorium(const char *ime) {
        strcpy (this->ime, ime);
    }
    ~Repozitorium() {}
    void pecatiOperativniSistemi() {
        cout << "Repozitorium: " << ime << endl;
        for (int i = 0; i < n; i++) {
            os[i].pecati();
        }
    }
    void izbrishi(const OperativenSistem &operativenSistem) {
        for (int i = 0; i < n; i++) {
            if (os[i].ednakviSe(operativenSistem)) {
                for (int j=i; j<n; j++) {
                    os[j]=os[j+1];
                }
                n--;
            }
        }
    }
    void dodadi(OperativenSistem &nov) {
        int k=0;
        for (int i = 0; i < n; i++) {
            if (os[i].ednakviSe(nov)) {
                if (os[i].get_verzija()<nov.get_verzija()) {
                    os[i]=nov;
                }
                k=1;
            }
        }
        if (k==0) {
            os[n]=nov;
            n++;
        }
    }
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}
*/


/*#include <iostream>

using namespace std;

class Number {
private:
    int n;
public:
    Number() {
        n=0;
    }
    Number(int n) {
        this->n = n;
    }
    void increaseNumber(int k) {
        if (n+k>100) {
            n=100;
            cout << "Sum is greater than 100" << endl;
        }
        else {
            n+=k;
        }
    }
    int get() {
        return n;
    }
};

int main() {
    Number obj1;
    int n;
    cin >> n;
    int cmd;
    int k;
    for (int i = 0; i < n; i++) {
        cin >> cmd;
        switch (cmd) {
            case 1: {
                cin >> k;
                Number obj2(k);
                cout << obj2.get() << endl;
                break;
            }
            case 2: {
                cin >> k;
                obj1.increaseNumber(k);
                cout << obj1.get() << endl;
                break;
            }
            case 3: {
                cin >> k;
                Number obj3(k);
                cin >> k;
                obj3.increaseNumber(k);
                cout << obj3.get() << endl;
                break;
            }
            default: {
                cout << obj1.get() << endl;
                break;
            }
        }
    }
}
*/