#include <iostream>
#include <cstring>

using namespace std;

struct Student {
    char name[20];
    char surname[20];
    int indeks;
    int poeni;
    void print() {
        cout << "Name: " << name << "   ";
        cout << "Surname: " << surname << "   ";
        cout << "Indeks: " << indeks << "   ";
        cout << "Poeni: " << poeni << endl;
    }
};

void read(Student &s) {
    int a, b, c, d;
    cin >> s.name >> s.surname >> s.indeks >> s.poeni;
}

void sort(Student s[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (s[j].poeni > s[j + 1].poeni) {
                Student temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}

int main() {
    Student s[100];
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        read(s[i]);
    }
    sort(s, n);
    cout << "======== ORDERED ========" << endl;
    for(int i = 0; i < n; ++i) {
        s[i].print();
    }
    return 0;
}
