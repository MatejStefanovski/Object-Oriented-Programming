#include <iostream>
#include <cstring>

using namespace std;

class Robot;
class Colony;

enum Type {
    EMPLOYER=0, WORKER, SCIENTIST
};

class Robot {
private:
    char name[51];
    int battery;
    Type category;
    friend void addBatteryForOthersCategory(Colony *c, int n, Type notfromthisCategory, int amount);
public:
    const char *getName() const {
        return name;
    }
    Type getCategory() const {
        return category;
    }
    Robot(const char *name="", int battery=0, Type category=EMPLOYER) {
        strcpy(this->name,name);
        this->battery = battery;
        this->category = category;
    }
    void addBattery(int increase) {
        int total=battery+increase;
        if (total>100) {
            battery=100;
        }else {
            battery+=increase;
        }
    }
    void print() const {
        cout<<name<<endl<<battery;
        if (category==EMPLOYER) {
            cout<<"EMPLOYER"<<endl;
        }else if (category==WORKER) {
            cout<<"WORKER"<<endl;
        }else {
            cout<<"SCIENTIST"<<endl;
        }
    }
};

class Colony {
private:
    char name[51];
    Robot robots[100];
    int n; //broj na roboti
public:
    friend void addBatteryForOthersCategory(Colony *c, int n, Type notfromthisCategory, int amount);
    int getN() const {
        return n;
    }
    Colony(char *name="") {
        strcpy(this->name,name);
        n=0;
    }
    void addRobot(const Robot &r) {
        for (int i=0;i<n;i++) {
            if (strcmp(robots[i].getName(),r.getName())==0 && robots[i].getCategory()==r.getCategory()){
                cout<<"This robot can't be added!"<<endl;
                return;
            }
        }
        if (n<100) {
            robots[n++]=r;
        }
    }
    void print() const {
        cout<<"Name: "<<name<<endl;
        for (int i=0;i<n;i++) {
            robots[i].print();
        }
    }
};

void addBatteryForOthersCategory(Colony *c, int n, Type notfromthisCategory, int amount) {
    for (int i=0;i<n;i++) {
        for (int j=0;j<c[i].getN();j++) {
            if (c[i].robots[j].getCategory()!=notfromthisCategory) {
                c[i].robots[j].addBattery(amount);
            }
        }
    }
}

int main() {

    return 0;
}

/*#include <iostream>
#include <cstring>

using namespace std;

enum Type {
    FAILED=0, PARTIAL, SUCCESS
};

class Satellite {
private:
    char name[20];
    char country[20];
public:
    Satellite() {
        strcpy(name, "");
        strcpy(country, "");
    }
    Satellite(char *name, char *country) {
        strcpy(this->name, name);
        strcpy(this->country, country);
    }
    void print() {
        cout << "Name: " << name << " Country: " << country << endl;
    }
};

class Mission {
private:
    Satellite s;
    char name[20];
    char date[20];
    int memory;
    Type type;
public:
    Mission(Satellite s={}, char *name="", char *date="", int memory=0, int(type)=0) {
        this->s = s;
        strcpy(this->name, name);
        strcpy(this->date, date);
        this->memory = memory;
        this->type=(Type)type;
    }
    void print() {
        cout << "Mission name: " << name << endl;
        cout << "Sattelite: ";
        s.print();
        cout<<" with memory: "<<memory<<"TB"<<endl;
        cout<<"Mission's date at: "<<date<<" Status: ";
        if (type==FAILED) {
            cout<<"Failed";
        }else if (type==PARTIAL) {
            cout<<"Partial";
        }else {
            cout<<"Success";
        }
        cout<<endl;
    }
};

int main() {
    int n;
    cin>>n;
    char name[11],date[11],namee[51],country[51];
    int memory;
    int type;
    Mission m[100];
    for (int i=0;i<n;i++) {
        cin>>name>>date; //imeto i datumot na misijata
        cin.ignore(); //za ako treba nov red za narednive 2
        cin.getline(namee,51);
        cin.getline(country,51); //edno do drugo se vnesuvaat, i + ima prazni mesta i vo namee i vo country, mora so getline
        cin>>memory>>type; //obichni integers
        Satellite s=Satellite(namee,country);
        m[i]=Mission(s,name,date,memory,type);
        m[i].print();
    }
    return 0;
}
*/