/*
1) Да се креира структура Engine во која што ќе се чуваат податоци за коњска сила / horsepower (int)
и вртежен момент / torque (int).

Потоа, да се креира структура Car во која што ќе  се чуваат податоци името на производителот
(char array) , која година е произведена колата (int) и кој мотор / engine (Engine) која што го користи/

На почетокот се внесува број N што озналува колку коли ќе се читаат од влез.

Да се направи функцијата:

void printCars(...)

која што ќе ги земе двете коли кои имаат најмала коњска сила,
и од нив две, ќе ја испечати колата што има поголем вртежен момент.
*/

/*#include <iostream>

using namespace std;

struct Engine {
    int horsepower;
    int torque;
};

struct Car {
    char name[25];
    int godina;
    Engine engine;
};

void printCars(Car car[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (car[j].engine.horsepower<car[j+1].engine.horsepower) {
                Car temp=car[j];
                car[j]=car[j+1];
                car[j+1]=temp;
            }
        }
    }
    if (car[n-1].engine.torque<car[n-2].engine.torque) {
        cout << car[n-1].name << " " << car[n-1].engine.torque << endl;
    }
    else {
        cout << car[n-2].name << " " << car[n-2].engine.torque << endl;
    }
}

int main() {
    int n;
    cin >> n;
    Car car[n];
    for (int i = 0; i < n; i++) {
        cin >> car[i].name >> car[i].godina;
        Engine e;
        cin >> e.horsepower >> e.torque;
        car[i].engine = e;
    }
    printCars(car, n);
    return 0;
}
*/

/*2)Да се креира класа BasketballPlayer која ќе ги чува следните информации:

име на кошаркарот (низа од знаци не подолга од 20 карактери)
презиме на кошаркарот (низа од знаци не подолга од 20 карактери)
број на дрес (цел број)
поени од прв натпревар (цел број)
поени од втор натпревар (цел број)
поени од трет натпревар (цел број)

Да се направат потребните методи за класата, како и метод за печатење на информации за кошаркарот во следен формат "Player: name surname with number: number has avg_pts points on average".

Од стандарден влез се внесуваат име, презиме, број на дрес и поени за сите три натпревари за еден кошаркар.

На стандарден излез се печатат информациите за кошаркарот.*/

/*#include <iostream>
#include <cstring>

using namespace std;

class BasketballPlayer {
private:
    char name[20];
    char surname[20];
    int br_dres;
    int p1;
    int p2;
    int p3;
public:
    BasketballPlayer(){}
    BasketballPlayer(char ime[],char prez[],int br,int pp1, int pp2, int pp3) {
        strcpy(name,ime);
        strcpy(surname,prez);
        br_dres = br;
        p1 = pp1;
        p2 = pp2;
        p3 = pp3;
    }
    float poeni() {
        return (p1 + p2 + p3)/3;
    }
    void display() {
        cout << "Player: " << name << " " << surname << " " << br_dres;
        cout << " has avg points: " << poeni() << endl;
    }
};

int main() {
    BasketballPlayer player1("Matej", "Stefanovski", 10, 30, 30, 40);
    player1.display();
    return 0;
}
*/



/*3)Да се дефинира класа Country во која ќе се чуваат информации за:

name(низа од максимум 100 карактери) име на државата

capital(низа од максимум 100 карактери) главен град

area(децимален број) - површина во илјада km2

population(децимален број) - популација во милиони.

Сите променливи внатре во класата треба да бидат приватни. Соодветно во рамките на класата да се дефинираат:

конструктор (без и со параметри)

деструктор

set методи

get методи

Да се дефинираат следните методи во класата:

display() која што ќе ги печати информациите за сметката во следниот формат:

Country: Guyana

Capital: Georgetown

Area: 214

Population: 0.8

Надвор од класата:

sortCountries(Country *countries, int n) која што ќе ги сортира државите растечки по нивната површина.
*/



#include <iostream>
#include <cstring>

using namespace std;

class Country {
private:
    char name[100];
    char capital[100];
    float area;
    float population;
public:
    Country() {
        strcpy(name, "");
        strcpy(capital, "");
        area = 0;
        population = 0;
    }
    Country(char *n, char *c, float a, float p) {
        strcpy(name, n);
        strcpy(capital, c);
        area = a;
        population = p;
    }
    ~Country() {}
    void setall(char *n, char *c, float a, float p) {
        strcpy(name, n);
        strcpy(capital, c);
        area = a;
        population = p;
    }
    void display() {
        cout << "Country: " << name << endl;
        cout << "Capital: " << capital << endl;
        cout << "Area: " << area << endl;
        cout << "Population: " << population << endl;
    }
    int get_area() {
        return area;
    }
};

void sortCountries(Country *countries, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (countries[j].get_area() > countries[j + 1].get_area()) {
                Country temp = countries[j];
                countries[j] = countries[j + 1];
                countries[j+1] = temp;
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    Country a[n];
    for (int i = 0; i < n; i++) {
        char name[100];
        char capital[100];
        float area;
        float population;
        cin.getline(name, 100);
        cin.getline(capital, 100);
        cin >> area >> population;
        cin.ignore();
        a[i].setall(name, capital, area, population);
    }
    sortCountries(a, n);
    for (int i = 0; i < n; i++) {
        a[i].display();
        cout << endl;
    }
    return 0;
}
