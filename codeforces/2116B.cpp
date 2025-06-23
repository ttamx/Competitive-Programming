#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    vector<mint> pw(n);
    pw[0]=1;
    for(int i=1;i<n;i++)pw[i]=pw[i-1]*2;
    int ma=0,mb=0;
    for(int i=0;i<n;i++){
        if(a[i]>a[ma])ma=i;
        if(b[i]>b[mb])mb=i;
        if(a[ma]>b[mb]){
            cout << pw[a[ma]]+pw[b[i-ma]] << " ";
        }else if(a[ma]<b[mb]){
            cout << pw[b[mb]]+pw[a[i-mb]] << " ";
        }else{
            cout << pw[a[ma]]+pw[max(a[i-mb],b[i-ma])] << " ";
        }
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}