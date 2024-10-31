#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

const int N=2e5+5;

mint pw[N];

void runcase(){
    pw[0]=1;
    for(int i=1;i<N;i++)pw[i]=pw[i-1]*2;
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
    }
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cout << pw[x] << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}