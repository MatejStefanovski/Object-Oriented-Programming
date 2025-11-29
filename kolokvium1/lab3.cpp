#include <iostream>
#include <cstring>

using namespace std;

class Scholarship;
class Student;

class Student {
private:
    char name[20];
    char surname[20];
    char faculty[20];
    float prosek;
    static int br_aplikacii_studenti;
    static int br_aplikacii_finki;
    friend class Scholarship;
    friend void studentsWithScholarship(Scholarship &s, int n);
public:
    Student() {
        strcpy(name, "");
        strcpy(surname, "");
        strcpy(faculty, "");
        prosek = 0;
        br_aplikacii_studenti++;
    }
    Student(char *name, char *surname, char *faculty, float prosek) {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        strcpy(this->faculty, faculty);
        this->prosek = prosek;
        br_aplikacii_studenti++;
        if (strcmp(name, "FINKI")==0 && prosek>9.0) {
            br_aplikacii_finki++;
        }
    }
    ~Student() {}
    bool finkiStudent() {
        return (strcmp(faculty,"FINKI")==0 && prosek>9.0);
    }
    void print() {
        cout << name << " " << surname << " " << faculty << " " << prosek << endl;
    }
};

class Scholarship {
private:
    char name[20];
    Student niza[20];
    int n;
    static int sredna_vrednost;
    friend void studentsWithScholarship(Scholarship &s, int n);
public:
    Scholarship() {
        strcpy(name, "");
        n=0;
    }
    Scholarship(char *name) {
        strcpy(this->name, name);
        n=0;
    }
    ~Scholarship() {}
    void addStudent(Student &student) {
        if (n<20) {
            niza[n]=student;
            n++;
            if (student.finkiStudent()) {
                sredna_vrednost+=student.prosek;
            }
        }
    }
    void print() {
        cout<<"Scholarship name: "<<name<<", total applicants: "<<n<<endl;
    }
};

int Student::br_aplikacii_studenti=0;
int Student::br_aplikacii_finki=0;
int Scholarship::sredna_vrednost=0;

void studentsWithScholarship(Scholarship &s, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (s.niza[j].prosek < s.niza[j + 1].prosek) {
                Student temp = s.niza[j];
                s.niza[j] = s.niza[j + 1];
                s.niza[j + 1] = temp;
            }
        }
    }
    cout<<"FINKI students with a scholarship"<<endl;
    int c=0;
    for (int i=0; i<n; i++) {
        if (c<3 && s.niza[i].finkiStudent()) {
            s.niza[i].print();
            c++;
        }
    }
    cout << "Scholarship data shows that " << 100.0*Student::br_aplikacii_finki/Student::br_aplikacii_studenti << "% of applicants are from FINKI, with an average grade of " << Scholarship::sredna_vrednost*1.0/Student::br_aplikacii_finki << endl;
}

int main() {
    char name[50], surname[50], faculty[50], scholarship_name[50];
    float average_grade;
    int n,case_;
    cin>>case_;
    if (case_ == 0)
        //Testing Student constructor
    {
        cout<<"--Testing finkiStudent method--"<<endl;
        Student s("Ana", "Denkova", "BAS", 9.89);
        cout<<s.finkiStudent();
    }
    else if (case_==1){
        //Testing addStudent and print method
        cout<<"--Testing addStudent and print method--"<<endl;
        Scholarship sc("ITCompany");
        Student s("Ana", "Denkova", "BAS", 9.89);
        sc.addStudent(s);
        sc.print();
    }
    else if (case_ == 2){
        cin>>scholarship_name;
        Scholarship sc(scholarship_name);
        cin>>n;
        for(int i=0; i<n; i++)
        {
            cin>>name>>surname>>faculty>>average_grade;
            Student s = Student(name, surname, faculty, average_grade);
            sc.addStudent(s);
        }
        sc.print();
        studentsWithScholarship(sc,n);
    }
    return 0;
}




/*#include <iostream>
#include <cstring>

using namespace std;

class County {
private:
    char name[50];
    int gdp;
public:
    County() {
        strcpy(name, "");
        gdp = 0;
    }
    County(char *name, int gdp) {
        strcpy(this->name, name);
        this->gdp = gdp;
    }
    ~County() {}
    char *getName() {
        return name;
    }
    int getGdp() {
        return gdp;
    }
};

class State {
private:
    County counties[20];
    char name[50];
    int numCounties;
    static float federalTax;
    bool redState;
public:
    State() {
        strcpy(name, "");
        numCounties = 0;
        redState = false;
    }
    State(County *counties, char *name, int numCounties, bool redState) {
        strcpy(this->name, name);
        this->numCounties = numCounties;
        this->redState = redState;
        for (int i = 0; i < numCounties; i++) {
            this->counties[i] = counties[i];
        }
    }
    char *getName() {
        return name;
    }
    static int getfederalTax() {
        return federalTax;
    }
    static void setfederalTax(float fedTax) {
        federalTax = fedTax;
    }
};

float State::federalTax = 15.5;

int main() {
    int n;
    cin >> n;
    char name[30] = "Richmond";
    County counties[3];
    counties[0] = County(name, 20);
    strcpy(name, "Bronx");
    counties[1] = County(name, 57);
    strcpy(name, "New York");
    counties[2] = County(name, 32);
    State state(counties, name, 3, false);
    switch(n){
        case 1: {
            cout << "---Testing constructors, getters, setters---" << endl;
            float fed;
            cin >> fed;
            State::setFederalTax(fed);
            if (State::getFederalTax() == 15.5) {
                cout << "State federal tax setter not OK!";
                break;
            }
            cout << counties[2].getName() << " Federal tax: " << State::getFederalTax() << " Full GDP: "
                 << state.getFullGDP();
            break;
        }
        case 2: {
            cout << "---Testing print method---" << endl;
            char name2[50];
            cin >> name2;
            County counties2[4];
            for (int i = 0; i < 3; ++i) {
                counties2[i] = counties[i];
            }
            counties2[3] = County(name2, 27);
            State state2(counties2, name, 4, false);
            state2.print();
            break;
        }
        case 3: {
            cout << "---Testing increaseFederalTax static method---" << endl;
            float increase;
            cin >> increase;
            cout << State::getFederalTax() << endl;
            State::increaseFederalTax(increase);
            cout << State::getFederalTax() << endl;
            cout << state.getFullGDP();
            break;
        }
        default:
            cout << "---Testing printStatesInGDPOrderByStateType---" << endl;
            County counties2[4];
            for (int i = 0; i < 3; ++i) {
                counties2[i] = counties[i];
            }
            strcpy(name, "Wayme");
            counties2[3] = County(name, 27);
            strcpy(name, "Ohio");
            State state2(counties2, name, 4, false);
            int numStates;
            cin >> numStates;
            numStates = numStates + 2;
            State states[numStates];
            states[0] = state;
            states[1] = state2;
            bool redStateSType;
            for (int i = 2; i < numStates; ++i) {
                char stateName[30];
                int numCounties;
                cin >> stateName >> numCounties >> redStateSType;
                County county[numCounties];
                for (int j = 0; j < numCounties; ++j) {
                    char ime[30];
                    int GDP;
                    cin >> ime >> GDP;
                    county[j] = County(ime, GDP);
                }
                states[i] = State(county, stateName, numCounties, redStateSType);
            }
            cout << "Red states: "<<endl;
            printStatesInGDPOrderByStateType(states, numStates, true);
            cout << "Blue states: "<<endl;
            printStatesInGDPOrderByStateType(states, numStates, false);

    }
    return 0;
}*/



/*#include <iostream>
#include <cstring>

using namespace std;

class Agency;
void findBestAgency(Agency *agencies, int numAgencies);

class Tour {
private:
    char destination[50];
    int duration;
    double price;
    static int totalTours;
    int passengers;
    friend void findBestAgency(Agency *agencies, int numAgencies);
public:
    Tour() {
        strcpy(destination, "");
        duration = 0;
        price = 0;
        passengers = 0;
        //totalTours++;
    }

    Tour(char *destination, int duration, double price, int passengers) {
        strcpy(this->destination, destination);
        this->duration = duration;
        this->price = price;
        this->passengers = passengers;
        totalTours++;
    }

    Tour(const Tour &t) {
        strcpy(this->destination, t.destination);
        this->duration = t.duration;
        this->price = t.price;
        this->passengers = t.passengers;
        //totalTours++;
    }

    ~Tour() {
        //totalTours--;
    }

    double profitByTour() const {
        return passengers * price;
    }

    void display() const {
        cout << "Destination: " << destination << ", Duration: " << duration << " days, Price: " << price << ", Passengers: " << passengers << endl;
    }

    static int getNumTours() {
        return totalTours;
    }
};

int Tour::totalTours = 0;

class Agency {
private:
    char name[50];
    Tour tours[10];
    int numTours;
    friend void findBestAgency(Agency *agencies, int numAgencies);
public:
    Agency() {
        strcpy(name, "");
        numTours = 0;
    }

    Agency(char *name, Tour *tours, int numTours) {
        strcpy(this->name, name);
        this->numTours = numTours;
        for (int i = 0; i < numTours; i++) {
            this->tours[i] = tours[i];
        }
    }

    void display() const {
        cout << "Travel Agency: " << name << endl;
        for (int i = 0; i < numTours; i++) {
            tours[i].display();
        }
    }

    void addTour(Tour tour) {
        if (numTours < 10) {
            tours[numTours] = tour;
            numTours++;
        }
    }

    void setName(const char *name) {
        strcpy(this->name, name);
    }
};

void findBestAgency(Agency *agencies, int numAgencies) {
    double max_profit = -1;
    int bestIndex = 0;
    for (int i = 0; i < numAgencies; i++) {
        double profit = 0;
        for (int j = 0; j < agencies[i].numTours; j++) {
            profit += agencies[i].tours[j].profitByTour();
        }
        if (profit > max_profit) {
            max_profit = profit;
            bestIndex = i;
        }
    }
    agencies[bestIndex].display();
}

int main() {
    int test_case_n;

    char name[50];
    char dest[50];
    int dur;
    double pr;
    int pass;

    cin >> test_case_n;

    if (test_case_n == 0) {
        cout << "Testing Tour c-tors, display function:" << endl;
        cin >> dest >> dur >> pr >> pass;
        Tour t1 = Tour(dest, dur, pr, pass);
        Tour t2 = Tour(t1);
        t1.display();
        t2.display();
    } else if (test_case_n == 1) {
        cout << "Testing Tour profitByTour function:" << endl;
        cin >> dest >> dur >> pr >> pass;
        Tour t1 = Tour(dest, dur, pr, pass);
        cout << t1.profitByTour() << endl;
    } else if (test_case_n == 2) {
        cout << "Testing Agency c-tor, display function:" << endl;
        Agency agency;
        cin >> name;
        agency.setName(name);
        int numTours;
        cin >> numTours;
        for (int j = 0; j < numTours; ++j) {
            cin >> dest >> dur >> pr >> pass;
            agency.addTour(Tour(dest, dur, pr, pass));
        }
        agency.display();
    } else if (test_case_n == 3) {
        cout << "Testing static field in Tour:" << endl;
        Agency agency[10];
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> name;
            agency[i].setName(name);
            int numTours;
            cin >> numTours;
            for (int j = 0; j < numTours; ++j) {
                cin >> dest >> dur >> pr >> pass;
                agency[i].addTour(Tour(dest, dur, pr, pass));
            }
        }
        cout << "Total number of tours: " << Tour::getNumTours() << endl;
    } else if (test_case_n == 4) {
        Agency agency[10];
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> name;
            agency[i].setName(name);
            int numTours;
            cin >> numTours;
            for (int j = 0; j < numTours; ++j) {
                cin >> dest >> dur >> pr >> pass;
                agency[i].addTour(Tour(dest, dur, pr, pass));
            }
        }
        findBestAgency(agency, n);
    }

    return 0;
}
*/




/*#include <iostream>
#include <cstring>

using namespace std;

class UserProfile;
class Achievement;
void showAchievementsProgress(UserProfile profiles[], int n, Achievement achievements[], int m);

class Achievement {
private:
    char name[100];
    char description[100];
    static int totalUserAchievements;
    friend class UserProfile;
    friend void showAchievementsProgress(UserProfile profiles[], int n, Achievement achievements[], int m);
public:
    Achievement() {
        strcpy(name, "");
        strcpy(description, "");
        //totalUserAchievements++;
    }
    Achievement(char *name, char *description) {
        strcpy(this->name, name);
        strcpy(this->description, description);
        //totalUserAchievements++;
    }
    Achievement(const Achievement &achievement) {
        strcpy(this->name, achievement.name);
        strcpy(this->description, achievement.description);
        //totalUserAchievements++;
    }
    ~Achievement() {
        //totalUserAchievements--;
    }
    void print() {
        cout << name << endl << description << endl;
    }
    bool operator==(const Achievement & a) {
        if (strcmp(this->name, a.name) == 0) {
            return true;
        }
        return false;
    }
    static void incrementTotalUserAchievements() {
        totalUserAchievements++;
    }
};

class UserProfile {
private:
    char name[100];
    Achievement achievements[50];
    int n;
    friend class Achievement;
    friend void showAchievementsProgress(UserProfile profiles[], int n, Achievement achievements[], int m);
public:
    UserProfile() {
        strcpy(name, "");
        n=0;
    }
    UserProfile(char *name) {
        strcpy(this->name, name);
        n=0;
    }
    void print() {
        cout << "User: " << name << endl;
        cout << "Achievements:" << endl;
        for (int i = 0; i < n; i++) {
            achievements[i].print();
        }
    }
    void addAchievement(const Achievement& achievement) {
        achievements[n] = achievement;
        n++;
        Achievement::incrementTotalUserAchievements();
    }
};

int Achievement::totalUserAchievements=0;

void showAchievementsProgress(UserProfile profiles[], int n, Achievement achievements[], int m) {
    for (int i = 0; i < m; i++) {
        achievements[i].print();
        int c = 0;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < profiles[j].n; k++) {
                if (profiles[j].achievements[k] == achievements[i]) {
                    c++;
                    break;
                }
            }
        }
        cout << "---Percentage of users who have this achievement: " << (c * 100.0 / n) << "%" << endl;
    }
    cout << "------Average completion rate of the game: " << Achievement::totalUserAchievements * 100.0 / (n * m) << "%" << endl;
}

int main() {
    char testcase[100];
    cin.getline(testcase, 100);

    int n;
    cin >> n;
    cin.ignore();

    char ignore[100];
    cin.getline(ignore, 100);
    UserProfile users[100];
    for (int i = 0; i < n; ++i) {
        char name[100];
        cin >> name;
        users[i] = UserProfile(name);
    }

    int m;
    cin >> m;
    cin.ignore();

    cin.getline(ignore, 100);
    Achievement achievements[100];
    for (int i = 0; i < m; ++i) {
        char name[100], description[100];
        cin.getline(name, 100);
        cin.getline(description, 100);
        achievements[i] = Achievement(name, description);
    }

    int k;
    cin >> k;
    cin.ignore();

    cin.getline(ignore, 100);
    for (int i = 0; i < k; ++i) {
        int numUser, numAchievement;
        cin >> numUser >> numAchievement;
        numUser -= 1;
        numAchievement -= 1;
        users[numUser].addAchievement(achievements[numAchievement]);
    }

    if (testcase[8] == 'A') {  // Testing Achievement methods.
        for (int i = 0; i < m; ++i) {
            achievements[i].print();
        }
        Achievement::incrementTotalUserAchievements();
    } else if (testcase[8] == 'U') {  // Testing UserProfile methods.
        for (int i = 0; i < n; ++i) {
            users[i].print();
        }
    } else {  // Testing showAchievementsProgress function.
        showAchievementsProgress(users, n, achievements, m);
    }

    return 0;
}*/



/*#include<iostream>
#include <cstring>

using namespace std;

class Mountain;
void sortMountainsByPeakElevation(Mountain mountains[], int n);

class MountainTrail {
private:
    char name[20];
    int length;
    double slope;
    friend class Mountain;
    friend void sortMountainsByPeakElevation(Mountain mountains[], int n);
public:
    MountainTrail() {
        length = 0;
        slope = 0;
        strcat(name, "");
    }
    MountainTrail(char *name, int length, double slope) {
        strcpy(this->name, name);
        this->length = length;
        this->slope = slope;
    }
    MountainTrail(const MountainTrail &m) {
        strcpy(this->name, m.name);
        this->length = m.length;
        this->slope = m.slope;
    }
    double difficulty() {
        return 1.0*(length*slope)/100;
    }
    void display() {
        cout << name << " " << length << " " << slope << endl;
    }
};

class Mountain {
private:
    char name[20];
    MountainTrail trails[5];
    int peak_elevation;
    static int num_mountains;
    friend class MountainTrail;
    friend void sortMountainsByPeakElevation(Mountain mountains[], int n);
public:
    Mountain() {
        num_mountains = 0;
        peak_elevation = 0;
        strcpy(name, "");
        num_mountains++;
    }
    Mountain(char *name, MountainTrail *trails, int peak_elevation) {
        strcpy(this->name, name);
        for (int i = 0; i < num_mountains; i++) {
            this->trails[i] = trails[i];
        }
        this->peak_elevation = peak_elevation;
        num_mountains++;
    }
    ~Mountain() {
        num_mountains--;
    }
    void display() {
        cout << name << ": " << peak_elevation << "m" << endl;
    }
    static int getNumMountains() {
        return num_mountains;
    }
};

int Mountain::num_mountains = 0;

void sortMountainsByPeakElevation(Mountain mountains[], int n) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n-1; j++) {
            if(mountains[j].peak_elevation>mountains[j+1].peak_elevation) {
                Mountain m=mountains[j];
                mountains[j]=mountains[j+1];
                mountains[j+1]=m;
            }
        }
    }
    for (int i=n-1; i>=0; i--) {
        mountains[i].display();
    }
}

int main() {

    int test_case_n;

    char trail_name[100];
    int trail_length;
    double trail_slope;

    char mountain_name[100];
    int mountain_peak_elevation;

    cin>>test_case_n;
    if (test_case_n == 0) {
        cout << "Testing MountainTrail c-tors, display function:"<<endl;
        cin >> trail_name >> trail_length >> trail_slope;
        MountainTrail mt = MountainTrail(trail_name, trail_length, trail_slope);
        MountainTrail mt2 = MountainTrail(mt);
        mt.display();
        mt2.display();
    } else if (test_case_n == 1) {
        cout << "Testing MountainTrail difficulty function:"<<endl;
        for (int i = 0; i < 5; ++i) {
            cin >> trail_name >> trail_length >> trail_slope;
            MountainTrail mt = MountainTrail(trail_name, trail_length, trail_slope);
            cout<<mt.difficulty()<<endl;
        }
    } else if (test_case_n == 2) {
        cout << "Testing Mountain c-tor, display function:"<<endl;
        MountainTrail trails[5];

        cin>>mountain_name>>mountain_peak_elevation;

        for (int i = 0; i < 5; ++i) {
            cin >> trail_name >> trail_length >> trail_slope;
            trails[i] = MountainTrail(trail_name, trail_length, trail_slope);
        }

        Mountain mountain = Mountain(mountain_name, trails, mountain_peak_elevation);
        mountain.display();
    } else if (test_case_n == 3) {
        cout << "Testing static field in Mountain:" <<endl;
        MountainTrail trails[5];

        cin>>mountain_name>>mountain_peak_elevation;

        for (int i = 0; i < 5; ++i) {
            cin >> trail_name >> trail_length >> trail_slope;
            trails[i] = MountainTrail(trail_name, trail_length, trail_slope);
        }

        for (int i = 0; i < 10; ++i) {
            Mountain mountain = Mountain(mountain_name, trails, mountain_peak_elevation);
        }

        Mountain m1 = Mountain(mountain_name, trails, mountain_peak_elevation);
        Mountain m2 = Mountain(mountain_name, trails, mountain_peak_elevation);
        Mountain m3 = Mountain(mountain_name, trails, mountain_peak_elevation);
        Mountain m4 = Mountain(mountain_name, trails, mountain_peak_elevation);
        Mountain m5 = Mountain(mountain_name, trails, mountain_peak_elevation);

        if(Mountain::getNumMountains() == 5) {
            cout<<"OK";
        } else {
            cout<<"Missing mountain count increment/decrement";
        }
    } else if (test_case_n == 4) {
        int M;
        cin>>M;
        cout<<"Testing order function:"<<endl;

        Mountain mountains[M];

        for (int i = 0; i < M; ++i) {
            cin>>mountain_name>>mountain_peak_elevation;
            MountainTrail trails[5];

            for (int j = 0; j < 5; ++j) {
                cin >> trail_name >> trail_length >> trail_slope;
                trails[j] = MountainTrail(trail_name, trail_length, trail_slope);
            }

            mountains[i] = Mountain(mountain_name, trails, mountain_peak_elevation);
        }

        sortMountainsByPeakElevation(mountains, M);
    }
}
*/