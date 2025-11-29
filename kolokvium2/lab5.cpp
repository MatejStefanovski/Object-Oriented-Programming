#include <iostream>
#include <cstring>

using namespace std;

class NBAPlayer {
protected:
    char *ime;
    char tim[40];
    double poeni;
    double asistencii;
    double skokovi;
public:
    NBAPlayer() {
        this->ime = new char[1];
        strcpy(this->ime, "");
        strcpy(tim, "");
        this->poeni = 0;
        this->asistencii = 0;
        this->skokovi = 0;
    }
    NBAPlayer(char *ime, char *tim, double poeni, double asistencii, double skokovi) {
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        strcpy(this->tim, tim);
        this->poeni = poeni;
        this->asistencii = asistencii;
        this->skokovi = skokovi;
    }
    NBAPlayer(const NBAPlayer &n) {
        this->ime=new char[strlen(n.ime)+1];
        strcpy(this->ime, n.ime);
        strcpy(this->tim, n.tim);
        this->poeni = n.poeni;
        this->asistencii = n.asistencii;
        this->skokovi = n.skokovi;
    }
    NBAPlayer &operator=(const NBAPlayer &n) {
        if (this != &n) {
            delete [] this->ime;
            this->ime=new char[strlen(n.ime)+1];
            strcpy(this->ime, n.ime);
            strcpy(this->tim, n.tim);
            this->poeni = n.poeni;
            this->asistencii = n.asistencii;
            this->skokovi = n.skokovi;
        }
        return *this;
    }
    virtual ~NBAPlayer() {
        delete[] this->ime;
    }
    virtual double rating() {
        return 0.45*poeni+0.3*asistencii+0.25*skokovi;
    }
    void print() {
        cout << "Ime: " << ime << endl;
        cout << "Tim: " << tim << endl;
        cout << "Poeni: " << poeni << endl;
        cout << "Asistencii: " << asistencii << endl;
        cout << "Skokovi: " << skokovi << endl;
    }
};

class AllStarPlayer:public NBAPlayer {
private:
    double prosek_poeni;
    double prosek_asistencii;
    double prosek_skokovi;
public:
    AllStarPlayer():NBAPlayer() {
        this->prosek_poeni = 0;
        this->prosek_asistencii = 0;
        this->prosek_skokovi = 0;
    }
    AllStarPlayer(NBAPlayer &n, double prosek_poeni, double prosek_asistencii, double prosek_skokovi):NBAPlayer(n) {
        this->prosek_poeni=prosek_poeni;
        this->prosek_asistencii=prosek_asistencii;
        this->prosek_skokovi=prosek_skokovi;
    }
    AllStarPlayer(char *ime, char *tim, double poeni, double asistencii, double skokovi, double prosek_poeni, double prosek_asistencii, double prosek_skokovi):NBAPlayer(ime, tim, poeni, asistencii, skokovi) {
        this->prosek_poeni=prosek_poeni;
        this->prosek_asistencii=prosek_asistencii;
        this->prosek_skokovi=prosek_skokovi;
    }
    AllStarPlayer(const AllStarPlayer &n):NBAPlayer(n) {
        this->prosek_poeni=n.prosek_poeni;
        this->prosek_asistencii=n.prosek_asistencii;
        this->prosek_skokovi=n.prosek_skokovi;
    }
    ~AllStarPlayer() {}
    double allStarRating() {
        return 0.3*prosek_poeni+0.4*prosek_asistencii+0.3*prosek_skokovi;
    }
    double rating() override {
        return (allStarRating()+NBAPlayer::rating())/2;
    }
    void print() {
        cout << "All Star rating: " << allStarRating() << endl;
        cout << "New Rating: " << rating() << endl;
    }
};

int main() {

    char name[50];
    char team[40];
    double points;
    double assists;
    double rebounds;
    double allStarPoints;
    double allStarAssists;
    double allStarRebounds;

    NBAPlayer * players = new NBAPlayer[5];
    AllStarPlayer * asPlayers = new AllStarPlayer[5];
    int n;
    cin >> n;

    if (n == 1) {

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            cin >> name >> team >> points >> assists >> rebounds;
            players[i] = NBAPlayer(name,team,points,assists,rebounds);
            players[i].print();
        }
    }
    else if (n == 2) {

        for (int i=0; i < 5; ++i){
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            players[i] = NBAPlayer(name,team,points,assists,rebounds);
            asPlayers[i] = AllStarPlayer(players[i],allStarPoints,allStarAssists,allStarRebounds);
        }

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            players[i].print();

        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            asPlayers[i].print();

    }
    else if (n == 3) {

        for (int i=0; i < 5; ++i){
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,
                                         allStarPoints,allStarAssists,allStarRebounds);
        }
        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            asPlayers[i].print();

    }

    delete [] players;
    delete [] asPlayers;
}
