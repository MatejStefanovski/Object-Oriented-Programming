#include <iostream>

using namespace std;

class Square {
private:
    int n;
    static int total;
public:
    Square(int n) {
        this->n = n;
        total++;
    }
    void print() {
        cout << n << endl;
        cout << total << endl;
    }
    static int getTotal() {
        return total;
    }
};

int Square::total=0;

int main() {
    int n;
    cin >> n;
    int m;
    cin >> m;
    Square s1(n);
    s1.print();
    Square s2(m);
    s2.print();
    return 0;
}