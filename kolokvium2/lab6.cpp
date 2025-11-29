#include <iostream>
#include <cstring>

using namespace std;

class MovieActor {
protected:
    char *name;
    char drzava[40];
    double pr_ocena;
    int br;
    double zarabotka;
public:
    MovieActor() {
        this->name = new char[40];
        strcpy(this->drzava, "");
        this->pr_ocena = 0;
        this->br = 0;
        this->zarabotka = 0;
    }
    MovieActor(char *name, char *drzava, double pr_ocena, int br, double zarabotka) {
        this->name = new char[40];
        strcpy(this->name, name);
        strcpy(this->drzava, drzava);
        this->pr_ocena = pr_ocena;
        this->br = br;
        this->zarabotka = zarabotka;
    }
    MovieActor(const MovieActor &m) {
        this->name = new char[40];
        strcpy(this->name, m.name);
        strcpy(this->drzava, m.drzava);
        this->pr_ocena = m.pr_ocena;
        this->br = m.br;
        this->zarabotka = m.zarabotka;
    }
    MovieActor &operator=(const MovieActor &m) {
        if (this != &m) {
            delete [] name;
            this->name = new char[40];
            strcpy(this->name, m.name);
            strcpy(this->drzava, m.drzava);
            this->pr_ocena = m.pr_ocena;
            this->br = m.br;
            this->zarabotka = m.zarabotka;
        }
        return *this;
    }
    virtual ~MovieActor() {
        delete [] name;
    }
    virtual double rating() {
        return pr_ocena*0.4+br*0.2+zarabotka*0.4;
    }
    virtual void print() {
        cout << name << " - " << drzava << endl;
        cout << "Average rating: " << pr_ocena << endl;
        cout << "Movies this year: " << br << endl;
        cout << "Total earnings: " << zarabotka << endl;
        cout << "Rating: " << rating() << endl;
    }
};

class OscarWinner:public MovieActor{
private:
    double pr_ocena_oskar;
    int br_oskar;
    double zarabotka_oskar;
public:
    OscarWinner():MovieActor() {
        this->pr_ocena_oskar = 0;
        this->br_oskar = 0;
        this->zarabotka_oskar = 0;
    }
    OscarWinner(MovieActor &m, double pr_ocena_oskar, int br_oskar, double zarabotka_oskar):MovieActor(m) {
        this->pr_ocena_oskar = pr_ocena_oskar;
        this->br_oskar = br_oskar;
        this->zarabotka_oskar = zarabotka_oskar;
    }
    OscarWinner(char *name, char *drzava, double pr_ocena, int br, double zarabotka, double pr_ocena_oskar, int br_oskar, double zarabotka_oskar):MovieActor(name, drzava, pr_ocena, br, zarabotka) {
        this->pr_ocena_oskar = pr_ocena_oskar;
        this->br_oskar = br_oskar;
        this->zarabotka_oskar = zarabotka_oskar;
    }
    OscarWinner(const OscarWinner &m):MovieActor(m) {
        this->pr_ocena_oskar = m.pr_ocena_oskar;
        this->br_oskar = m.br_oskar;
        this->zarabotka_oskar = m.zarabotka_oskar;
    }
    OscarWinner &operator=(const OscarWinner &m) {
        if (this != &m) {
            delete [] name;
            this->name = new char[40];
            strcpy(this->name, m.name);
            strcpy(this->drzava, m.drzava);
            this->pr_ocena = m.pr_ocena;
            this->br = m.br;
            this->zarabotka = m.zarabotka;
            this->pr_ocena_oskar=m.pr_ocena_oskar;
            this->br_oskar=m.br_oskar;
            this->zarabotka_oskar=m.zarabotka_oskar;
        }
        return *this;
    }
    ~OscarWinner() {
        //delete [] name;
    }
    double oscarRating() {
        return pr_ocena_oskar*0.6+br_oskar*0.1+zarabotka_oskar*0.3;
    }
    double rating() override{
        return oscarRating();
    }
    void print() override{
        MovieActor::print();
        cout << "Oscar rating: " << oscarRating() << endl << "New rating: " << pr_ocena_oskar << endl;
    }
};

int main() {
char name[100];
    char country[41];
    double avg_rating;
    int num_movies;
    double earnings;
    double post_avg_rating;
    int post_num_movies;
    double post_earnings;

    int n;
    cin >> n;

    if (n == 1) {
        // Test MovieActor basic functionality
        cout << "MOVIE ACTORS:" << endl;
        cout << "=====================================" << endl;
        int numActors;
        cin >> numActors;

        MovieActor* actors = new MovieActor[numActors];

        for (int i = 0; i < numActors; ++i) {
            cin >> name >> country >> avg_rating >> num_movies >> earnings;
            actors[i] = MovieActor(name, country, avg_rating, num_movies, earnings);
            actors[i].print();
            cout << "-------------------------" << endl;
        }

        delete[] actors;
    }
    else if (n == 2) {
        // Test MovieActor and create OscarWinner from it
        int numActors;
        cin >> numActors;

        MovieActor* actors = new MovieActor[numActors];
        OscarWinner* oscarWinners = new OscarWinner[numActors];
for (int i = 0; i < numActors; ++i) {
            cin >> name >> country >> avg_rating >> num_movies >> earnings;
            cin >> post_avg_rating >> post_num_movies >> post_earnings;

            actors[i] = MovieActor(name, country, avg_rating, num_movies, earnings);
            oscarWinners[i] = OscarWinner(actors[i], post_avg_rating, post_num_movies, post_earnings);
        }

        cout << "MOVIE ACTORS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < numActors; ++i) {
            actors[i].print();
            cout << "-------------------------" << endl;
        }

        cout << "OSCAR WINNERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < numActors; ++i) {
            oscarWinners[i].print();
            cout << "-------------------------" << endl;
        }

        delete[] actors;
        delete[] oscarWinners;
    }
    else if (n == 3) {
        // Test OscarWinner with all arguments constructor
        int numWinners;
        cin >> numWinners;

        OscarWinner* oscarWinners = new OscarWinner[numWinners];

        for (int i = 0; i < numWinners; ++i) {
            cin >> name >> country >> avg_rating >> num_movies >> earnings;
            cin >> post_avg_rating >> post_num_movies >> post_earnings;

            oscarWinners[i] = OscarWinner(name, country, avg_rating, num_movies, earnings,
                                          post_avg_rating, post_num_movies, post_earnings);
        }

        cout << "OSCAR WINNERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < numWinners; ++i) {
            oscarWinners[i].print();
            cout << "-------------------------" << endl;
        }
delete[] oscarWinners;
    }
    else if (n == 4) {
        // Test copy constructor and operator= for MovieActor
        MovieActor actor1;
        cin >> name >> country >> avg_rating >> num_movies >> earnings;
        actor1 = MovieActor(name, country, avg_rating, num_movies, earnings);

        MovieActor actor2(actor1); // Using copy constructor
        MovieActor actor3;
        actor3 = actor1;           // Using operator=

        cout << "ORIGINAL:" << endl;
        actor1.print();
        cout << "-------------------------" << endl;

        cout << "COPY CONSTRUCTOR:" << endl;
        actor2.print();
        cout << "-------------------------" << endl;

        cout << "OPERATOR=:" << endl;
        actor3.print();
        cout << "-------------------------" << endl;
    }
    else if (n == 5) {
        // Test copy constructor and operator= for OscarWinner
        OscarWinner winner1;
        cin >> name >> country >> avg_rating >> num_movies >> earnings;
        cin >> post_avg_rating >> post_num_movies >> post_earnings;

        winner1 = OscarWinner(name, country, avg_rating, num_movies, earnings,
                              post_avg_rating, post_num_movies, post_earnings);

        OscarWinner winner2(winner1); // Using copy constructor
        OscarWinner winner3;
        winner3 = winner1;            // Using operator=

        cout << "ORIGINAL:" << endl;
        winner1.print();
        cout << "-------------------------" << endl;

        cout << "COPY CONSTRUCTOR:" << endl;
        winner2.print();
        cout << "-------------------------" << endl;

        cout << "OPERATOR=:" << endl;
        winner3.print();
        cout << "-------------------------" << endl;
    }
    return 0;
}


/*#include <iostream>
#include <cstring>

using namespace std;

class Room {
protected:
    int br_soba;
    int cena;
public:
    Room() {
        br_soba = 0;
        cena = 0;
    }
    Room(int br_soba, int cena) {
        this->br_soba = br_soba;
        this->cena = cena;
    }
    Room(const Room& room) {
        this->br_soba = room.br_soba;
        this->cena = room.cena;
    }
    Room& operator=(const Room& room) {
        if (this != &room) {
            this->br_soba = room.br_soba;
            this->cena = room.cena;
        }
        return *this;
    }
    virtual float getPrice() {
        return cena;
    }
    virtual void print() {
        cout << "Broj na Soba: " << br_soba << " Cena za nokjevanje: " << getPrice() << " evra" << endl;
    }
};

class StandardRoom : public Room{
private:
    bool hasBalcony;
public:
    StandardRoom():Room() {
        hasBalcony = false;
    }
    StandardRoom(int br_soba, int cena, bool hasBalcony):Room(br_soba, cena) {
        this->hasBalcony = hasBalcony;
    }
    float getPrice() override{
        if (hasBalcony) {
            return cena-cena*0.05;
        }
        else {
            return cena;
        }
    }
    void print() override{
        if (hasBalcony) {
            cout << "Broj na Soba: " << br_soba << " Cena za nokjevanje: " << getPrice() << " evra - so terasa" << endl;
        }
        else {
            cout << "Broj na Soba: " << br_soba << " Cena za nokjevanje: " << getPrice() << " evra - bez terasa" << endl;
        }
    }
};

class LuxuryRoom: public Room {
private:
    bool hasJacuzzi;
public:
    LuxuryRoom():Room() {
        hasJacuzzi = false;
    }
    LuxuryRoom(int br_soba, int cena, bool hasJacuzzi):Room(br_soba, cena) {
        this->hasJacuzzi = hasJacuzzi;
    }
    float getPrice() override{
        if (hasJacuzzi) {
            return cena+cena*0.2;
        }
        else {
            return cena;
        }
    }
    void print() override{
        if (hasJacuzzi) {
            cout << "Broj na Soba: " << br_soba << " Cena za nokjevanje: " << getPrice() << " evra - so Jacuzzi" << endl;
        }
        else {
            cout << "Broj na Soba: " << br_soba << " Cena za nokjevanje: " << getPrice() << " evra - bez Jacuzzi" << endl;

        }
    }
};

int main() {
    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        // Test Room class
        int number, price;
        cin >> number >> price;
        Room r1(number, price);
        Room r2 = r1;  // Copy constructor
        Room r3;
        r3 = r1;       // Assignment operator

        r1.print();
        r2.print();
        r3.print();
    }
    else if (testCase == 2) {
        // Test StandardRoom
        int number, price;
        bool hasBalcony;
        cin >> number >> price >> hasBalcony;

        StandardRoom sr(number, price, hasBalcony);
        sr.print();
    }
    else if (testCase == 3) {
        // Test LuxuryRoom
        int number, price;
        bool hasJacuzzi;
        cin >> number >> price >> hasJacuzzi;

        LuxuryRoom lr(number, price, hasJacuzzi);
        lr.print();
    }
    else if (testCase == 4) {
        // Polymorphism test
        int n;
        cin >> n;
        Room* rooms[100];

        for (int i = 0; i < n; ++i) {
            string type;
            cin >> type;

            int number, price;
            cin >> number >> price;

            if (type == "Standard") {
                bool hasBalcony;
                cin >> hasBalcony;
                rooms[i] = new StandardRoom(number, price, hasBalcony);
            } else if (type == "Luxury") {
                bool hasJacuzzi;
                cin >> hasJacuzzi;
                rooms[i] = new LuxuryRoom(number, price, hasJacuzzi);
            } else {
                rooms[i] = new Room(number, price);
            }
        }

        for (int i = 0; i < n; ++i) {
            rooms[i]->print();
        }

        for (int i = 0; i < n; ++i) {
            delete rooms[i];
        }
    }
    return 0;
}
*/