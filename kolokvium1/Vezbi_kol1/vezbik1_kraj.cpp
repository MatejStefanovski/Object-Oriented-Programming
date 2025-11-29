#include <iostream>
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
    char *getName() {
        return name;
    }
    int getGdp() {
        return gdp;
    }
};

class State {
private:
    County counties[50];
    char name[50];
    int numCounties;
    static float federalTax;
    bool redState;
    friend void printStatesInGDPOrderByStateType(State states[], int numStates, bool redStates);
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
    static float getFederalTax() {
        return federalTax;
    }
    static float setFederalTax(float fedTax) {
        federalTax = fedTax;
    }
    static void increaseFederalTax(float increase) {
        federalTax += increase;
    }
    float getFullGDP(){
        float total=0;
        for (int i=0;i<numCounties;i++) {
            total=total+(counties[i].getGdp()-counties[i].getGdp()*federalTax/100.0);
        }
        return total;
    }
    void print() {
        cout << "State of " << name << endl;
        for (int i = 0; i < numCounties; i++) {
            cout << counties[i].getName() << endl;
        }
    }
    bool isRedState() {
        return redState;
    }
};

float State::federalTax = 15.5;

void printStatesInGDPOrderByStateType(State states[], int numStates, bool redStates) {
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < numStates-1; j++) {
            if (states[j].getFullGDP()<states[j+1].getFullGDP()) {
                swap(states[j], states[j+1]);
            }
        }
    }
    if (redStates) {
        for (int i = 0; i < numStates; i++) {
            if (states[i].isRedState()) {
                cout << states[i].getName() << endl;
            }
        }
    }
    else {
        for (int i = 0; i < numStates; i++) {
            if (!states[i].isRedState()) {
                cout << states[i].getName() << endl;
            }
        }
    }
}

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
}


/*#include <iostream>
#include <cstring>
using namespace std;
class State;
class County;
class County {
private:
    char name[51];
    int gdp;
public:
    friend class State;
    friend void printStatesInGDPOrderByStateType(State states[], int n, bool red);
    const char *getName() const {
        return name;
    }
    int getGDP() const {
        return gdp;
    }
    County(const char *name="", int gdp=0) {
        strcpy(this->name, name);
        this->gdp = gdp;
    }
    void print() const {
        cout<<name<<endl;
    }
};
class State {
private:
    County counties[100];
    char name[51];
    int n;
    static float FEDERAL_TAX;
    bool redState;
public:
    friend void printStatesInGDPOrderByStateType(State states[], int n, bool red);
    static float getFederalTax() {
        return FEDERAL_TAX;
    }
    const char *getName() const {
        return name;
    }
    static void setFederalTax(float tax) {
        FEDERAL_TAX = tax;
    }
    static void increaseFederalTax(float increase) {
        FEDERAL_TAX += increase;
    }
    float getFullGDP() const{
        float total=0;
        for (int i=0;i<n;i++) {
            total=total+(counties[i].getGDP()-counties[i].getGDP()*FEDERAL_TAX/100.0);
        }
        return total;
    }
    State(County *counties=nullptr, const char *name="", int n=0, bool redState=false) {
        if (counties) {
            for (int i=0;i<100;i++) {
                this->counties[i] = counties[i];
            }
        }
        strcpy(this->name, name);
        this->n = n;
        this->redState = redState;
    }
    void print() const{
        cout<<"State of "<<name<<endl;
        for (int i=0;i<n;i++) {
            counties[i].print();
        }
    }
};
void printStatesInGDPOrderByStateType(State states[], int n, bool red) {
    //ako red e tochno, printaj reds, inache blues states !!!
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            if (states[j].getFullGDP()<states[j+1].getFullGDP()) {
                swap(states[j], states[j+1]);
            }
        }
    }
    if (red) {
        for (int i=0;i<n;i++) {
            if (states[i].redState) {
                cout<<states[i].name<<endl;
            }
        }
    }else {
        for (int i=0;i<n;i++) {
            if (!states[i].redState) {
                cout<<states[i].name<<endl;
            }
        }
    }
}
float State::FEDERAL_TAX = 15.5;

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