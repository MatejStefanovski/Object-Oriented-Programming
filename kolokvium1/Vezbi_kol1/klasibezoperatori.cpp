#include <iostream>

using namespace std;

class List {
private:
    int *niza;
    int n;
public:
    List() {
        n = 0;
    }
    List(int *niza, int n) {
        this->n=n;
        this->niza=new int[n];
        for(int i=0;i<n;i++) {
            this->niza[i]=niza[i];
        }
    }
    List(const List &l) {
        this->n=l.n;
        this->niza=new int[l.n];
        for(int i=0;i<l.n;i++) {
            this->niza[i]=l.niza[i];
        }
    }
    List &operator=(const List &l) {
        if(this!=&l) {
            delete [] this->niza;
            this->n=l.n;
            this->niza=new int[l.n];
            for(int i=0;i<l.n;i++) {
                this->niza[i]=l.niza[i];
            }
        }
        return *this;
    }
    ~List() {
        delete[] this->niza;
    }
    int sum() {
        int temp=0;
        for (int i=0;i<n;i++) {
            temp+=this->niza[i];
        }
        return temp;
    }
    double average() {
        double temp=sum();
        return temp/n;
    }
    void pecati() {
        cout << n << ": ";
        for (int i=0;i<n;i++) {
            cout << this->niza[i] << " ";
        }
        cout << "sum: " << sum() << " average: " << average() << endl;
    }
};

class ListContainer {
private:
    List *list;
    int n;
    int obidi;
public:
    ListContainer() {
        n = 0;
        obidi = 0;
        list = nullptr;
    }

    ListContainer(const ListContainer &lc) {
        n = lc.n;
        obidi = lc.obidi;
        list = new List[n];
        for (int i = 0; i < n; i++) {
            list[i] = lc.list[i];
        }
    }

    ListContainer &operator=(const ListContainer &lc) {
        if (this != &lc) {
            delete[] list;
            n = lc.n;
            obidi = lc.obidi;
            list = new List[n];
            for (int i = 0; i < n; i++) {
                list[i] = lc.list[i];
            }
        }
        return *this;
    }

    ~ListContainer() {
        delete[] list;
    }

    void addNewList(List l) {
        obidi++;
        for (int i = 0; i < n; i++) {
            if (list[i].sum() == l.sum()) {
                return;
            }
        }

        List *temp = new List[n + 1];
        for (int i = 0; i < n; i++) {
            temp[i] = list[i];
        }
        temp[n++] = l;

        delete[] list;
        list = temp;
    }

    void print() const {
        if (n == 0) {
            cout << "The list is empty." << endl;
        } else {
            for (int i = 0; i < n; i++) {
                cout << "List number: " << i + 1 << " List info: ";
                list[i].pecati();
            }
            cout << "Sum: " << sum() << " Average: " << average() << endl;
            cout << "Successful attempts: " << n << " Failed attempts: " << obidi - n << endl;
        }
    }

    int sum() const {
        int total = 0;
        for (int i = 0; i < n; i++) {
            total += list[i].sum();
        }
        return total;
    }

    double average() const {
        int totalElements = 0;
        for (int i = 0; i < n; i++) {
            totalElements += list[i].sum();
        }

        if (totalElements == 0) return 0;

        return (double)sum() / totalElements;
    }
};

int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}
