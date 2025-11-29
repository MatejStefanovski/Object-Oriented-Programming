#include <iostream>

using namespace std;

int main() {
    long long n, prethoden;
    cin>>n;
    long long a, zbir=0;
    bool flag=false;
    for(long long i=0;i<n;i++) {
        cin>>a;
        if (!flag) {
            zbir+=a;
            flag=true;
            prethoden=a;
        }
        else {
            if (a!=prethoden+1) {
                zbir+=a;
            }
            prethoden=a;
        }
    }
    cout<<zbir;
    return 0;
}
