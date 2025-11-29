#include <iostream>

using namespace std;

class Letter {
private:
    char ch;
public:
    Letter() {
        ch = 'a';
    }
    Letter(char ch) {
        this->ch = ch;
    }
    void lowerLetter() {
        if (isalpha(this->ch)) {
            this->ch = tolower(this->ch);
        }
        else {
            cout << "Character is not a letter" << endl;
        }
    }
    void print() {
        cout << this->ch << endl;
    }
    void set(char ch) {
        this->ch = ch;
    }
};

int main() {
    Letter obj;
    int n;
    cin >> n;
    int cmd;
    char k;
    for (int i = 0; i < n; i++) {
        cin >> cmd;
        switch (cmd) {
            case 1: {
                cin >> k;
                obj.set(k);
                obj.print();
                break;
            }
            case 2: {
                obj.lowerLetter();
                obj.print();
                break;
            }
            case 3: {
                cin >> k;
                Letter obj2;
                obj2.set(k);
                obj2.lowerLetter();
                obj2.print();
                break;
            }
            default: {
                obj.print();
                break;
            }
        }
    }
}


/*#include <iostream>
#include <cstring>

using namespace std;

class Letter {
private:
    char ch;
public:
    Letter() {
        ch = 'a';
    }
    Letter(char c) {
        ch=c;
    }
    void upperLetter() {
        if (isalpha(ch)) {
            ch = toupper(ch);
        }
        else {
            cout << "Character is not a letter" << endl;
        }
    }
    char get() {
        return ch;
    }
};

int main() {
    Letter obj;
    int n;
    cin >> n;
    int cmd;
    char k;
    for (int i = 0; i < n; i++) {
        cin >> cmd;
        switch (cmd) {
            case 1: {
                cin >> k;
                obj = Letter(k);
                cout << obj.get() << endl;
                break;
            }
            case 2: {
                obj.upperLetter();
                cout << obj.get() << endl;
                break;
            }
            case 3: {
                cin >> k;
                Letter obj2(k);
                obj2.upperLetter();
                cout << obj2.get() << endl;
                break;
            }
            default: {
                cout << obj.get() << endl;
                break;
            }
        }
    }
}*/


/*#include <iostream>

using namespace std;

class Temperature {
private:
    float temperature;
public:
    Temperature() {
        temperature = 0;
    }
    Temperature(float temp) {
        temperature = temp;
    }
    void set(float temp) {
        temperature=temp;
    }
    void changeTemp() {
        if (temperature<0) {
            temperature+=1;
        }
        else {
            temperature-=1;
        }
    }
    void print() {
        cout << temperature << endl;
    }
};

int main() {
    Temperature obj;
    int n;
    cin >> n;
    int cmd;
    float k;
    for (int i = 0; i < n; i++) {
        cin >> cmd;
        switch (cmd) {
            case 1: {
                cin >> k;
                obj.set(k);
                obj.print();
                break;
            }
            case 2: {
                obj.changeTemp();
                obj.print();
                break;
            }
            case 3: {
                Temperature obj3;
                cin >> k;
                obj3.set(k);
                obj3.changeTemp();
                obj3.print();
                break;
            }
            default: {
                obj.print();
                break;
            }
        }
    }
}
*/

/*#include <iostream>

using namespace std;

class Temperature {
private:
    float temperature;
public:
    Temperature() {
        temperature = 0;
    }
    Temperature(float temp) {
        temperature = temp;
    }
    float get() {
        return temperature;
    }
    void changeTemp() {
        if (temperature>=0) {
            temperature += 1;
        }
        else {
            temperature -= 1;
        }
    }
};

int main() {
    Temperature obj1;
    int n;
    cin >> n;
    int cmd;
    float k;
    for (int i = 0; i < n; i++) {
        cin >> cmd;
        switch (cmd) {
            case 1: {
                cin >> k;
                Temperature obj2(k);
                cout << obj2.get() << endl;
                break;
            }
            case 2: {
                obj1.changeTemp();
                cout << obj1.get() << endl;
                break;
            }
            case 3: {
                cin >> k;
                Temperature obj3(k);
                obj3.changeTemp();
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


/*#include <iostream>

using namespace std;

class Number {
private:
    int num;
public:
    Number(){}
    Number(int num) {
        this->num = num;
    }
    void set(int num) {
        this->num = num;
    }
    void decreaseNumber(int num) {
        if (this->num - num >=0) {
            this->num-=num;
        }
        else {
            this->num=0;
            cout << "Difference is less than 0" << endl;
        }
    }
    void print() {
        cout << this->num << endl;
    }
};

int main() {
    Number obj;
    int n;
    cin >> n;
    int cmd;
    int k;
    for (int i = 0; i < n; i++) {
        cin >> cmd;
        switch (cmd) {
            case 1: {
                cin >> k;
                obj.set(k);
                obj.print();
                break;
            }
            case 2: {
                cin >> k;
                obj.decreaseNumber(k);
                obj.print();
                break;
            }
            case 3: {
                Number obj2;
                cin >> k;
                obj2.set(k);
                cin >> k;
                obj2.decreaseNumber(k);
                obj2.print();
                break;
            }
            default: {
                obj.print();
                break;
            }
        }
    }
}*/


/*#include <iostream>

using namespace std;

class Number {
private:
    int number;
public:
    Number(int n=0) {
        number = n;
    }
    int get() {
        return number;
    }
    int increaseNumber(int n) {
        if (number+n<=100) {
            number = number + n;
        }
        else {
            number=100;
            cout<<"Sum is greater than 100"<<endl;
        }
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