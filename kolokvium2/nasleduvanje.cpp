#include <iostream>
#include <string>

using namespace std;

class DebitAccount {
protected:
    string name;
    long long number;
    double balance;
public:
    DebitAccount() {
        name = "";
        number = 0;
        balance = 0;
    }
    DebitAccount(string name, long long number, double balance) {
        this->name = name;
        this->number = number;
        this->balance = balance;
    }
    void showInfo() {
        cout << "Name: " << name << " Debit card number: " << number << " - Balance: " << balance << endl;
    }
    void deposit(double ammount) {
        if (ammount<0) {
            cout << "ammount must be greater than zero" << endl;
            return;
        }
        balance += ammount;
    }
    void withdraw(double ammount) {
        if (balance-ammount<0) {
            cout << "Balance is negative." << endl;
            return;
        }
        else if (ammount<0) {
            cout << "ammount must be greater than zero" << endl;
            return;
        }
        else {
            balance -= ammount;
        }
    }
    double getBalance() {
        return balance;
    }
};

class CreditAccount:public DebitAccount {
private:
    double limit;
    double interest;
    double minus;
public:
    CreditAccount() {
        name = "";
        number = 0;
        balance = 0;
        limit = 0;
        minus = 0;
        interest=0;
    }
    CreditAccount(string name, long long number, double balance, double limit) {
        this->name = name;
        this->number = number;
        this->balance = balance;
        this->limit = limit;
        this->minus = 0;
        this->interest = 0;
    }
    CreditAccount(string name, long long number, double balance, double limit, double interest, double minus) {
        this->name = name;
        this->number = number;
        this->balance = balance;
        this->limit = limit;
        this->minus = minus;
        this->interest = interest;
    }
    void withdraw(double ammount) {
        int balance = getBalance();
        if (ammount<=balance) {
            DebitAccount::withdraw(ammount);
        }
        else if (ammount <= balance + limit - minus) {
            double advance = ammount - balance;
            this->minus +=advance * (1.0 + interest);
            cout<<"Minus: " << advance << endl << "Minus with interest: " << advance*interest<<endl;
            deposit(advance);
            DebitAccount::withdraw(ammount);

        } else {
            cout << "The bank is not giving you that much money..." << endl;
            this->showInfo();
        }
    }
    void showInfo() {
        DebitAccount::showInfo();
        cout << "Limit: " << limit << " Minus: " << minus << " Interest: " << interest << endl;
    }
    double getInterest() {
        return interest;
    }
};

int main() {
    DebitAccount d("Pero Perovski", 6, 100000);
    CreditAccount ca("Mitko Mitkovski", 10, 5000, 1000);
    d.showInfo();
    d.deposit(50000);
    d.withdraw(600000);
    d.showInfo();
    ca.showInfo();
    ca.deposit(500);
    ca.showInfo();
    ca.withdraw(6200);
    ca.showInfo();
    return 0;
}



/*#include <iostream>
#include <string>

using namespace std;

class TennisPlayer {
protected:
    string name;
    string surname;
    bool playsInLeague;
public:
    TennisPlayer() {
        name="";
        surname="";
        playsInLeague = false;
    }
    TennisPlayer(string name, string surname) {
        this->name=name;
        this->surname=surname;
        playsInLeague = false;
    }
    TennisPlayer(string name, string surname, bool playsInLeague) {
        this->name = name;
        this->surname = surname;
        this->playsInLeague = playsInLeague;
    }
    bool PlaysInLeague() {
        return playsInLeague;
    }
    void setPlaysInLeague(bool pl) {
        this->playsInLeague = pl;
    }
    ~TennisPlayer() {}
    friend ostream& operator<<(ostream& out, const TennisPlayer& p) {
        out << "Name: " << p.name << " Surname: " << p.surname << " - ";
        if (p.playsInLeague) {
            out << "Plays in League" << endl;
        }
        else {
            out << "Does not play in league" << endl;
        }
        return out;
    }
};

class RankedTennisPlayer : public TennisPlayer {
private:
    int rank;
public:
    RankedTennisPlayer() {
        rank = 0;
        name="";
        surname="";
        playsInLeague = false;
    }
    RankedTennisPlayer(string name, string surname, bool playsInLeague, int rank) {
        this->name = name;
        this->surname = surname;
        this->playsInLeague = playsInLeague;
        this->rank = rank;
    }
    RankedTennisPlayer(const TennisPlayer &t, int rank=0):TennisPlayer(t) {
        this->rank = rank;
    }
    ~RankedTennisPlayer() {}
    friend ostream& operator<<(ostream& out, const RankedTennisPlayer& p) {
        out << "Ranked tennis player: " << endl;
        out << "Name: " << p.name << " Surname: " << p.surname << " - rank: " << p.rank << endl;
        return out;
    }
};

int main(){
    TennisPlayer rf("Roger", "Federer");
    TennisPlayer ng("Novak", "Djokovikj");
    cout << rf;
    cout << ng;
    RankedTennisPlayer rn("Rafael", "Nadal", true, 2750);
    cout << rn;
    TennisPlayer tp = rn;
    cout << tp;
    RankedTennisPlayer copy(ng, 3320);
    cout << copy;
    return 0;
}
*/