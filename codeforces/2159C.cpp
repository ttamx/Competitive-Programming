#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+1);
    for(auto &x:a){
        cin >> x;
    }
    for(int i=1;i<=n;i++){
        if(a[i]>n){
            cout << 0 << "\n";
            return;
        }
        if(a[i]<=0){
            continue;
        }
        if(a[a[i]]==-1){
            a[a[i]]=i;
        }
        if(a[a[i]]!=i){
            cout << 0 << "\n";
            return;
        }
    }
    int cnt=0;
    for(int i=1;i<n;i++){
        if(a[i]==-1){
            cnt++;
        }
    }
    vector<mint> pw(n+2);
    pw[0]=1;
    for(int i=1;i<=n+1;i++){
        pw[i]=pw[i-1]*2;
    }
    mint ans=0;
    if(a[n]!=-1){
        mint ways=1;
        for(int i=cnt,t=0;i>=0;i-=2,t++){
            ans+=ways*pw[i]*comb.ifac(t);
            ways*=comb.C(i,2);
        }
    }else{
        {
            mint ways=1;
            for(int i=cnt,t=0;i>=0;i-=2,t++){
                ans+=ways*pw[i]*comb.ifac(t);
                ways*=comb.C(i,2);
            }
        }
        {
            mint ways=cnt;
            for(int i=cnt-1,t=0;i>=0;i-=2,t++){
                ans+=ways*pw[i]*comb.ifac(t);
                ways*=comb.C(i,2);
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}

/*
0 0 3
0 2 3
0 3 2
1 0 3
1 2 3
1 3 2
2 1 3
3 0 1
3 2 1
9

0 0 0 4
0 0 3 4
0 0 4 3
0 2 0 4
0 2 3 4
0 2 4 3
0 3 2 4
0 4 0 2
0 4 3 2
1 0 0 4
1 0 3 4
1 0 4 3
1 2 0 4
1 2 3 4
1 2 4 3
1 3 2 4
1 4 0 2
1 4 3 2
2 1 0 4
2 1 3 4
2 1 4 3
3 0 1 4
3 2 1 4
3 4 1 2
4 0 0 1
4 0 3 1
4 2 0 1
4 2 3 1
4 3 2 1
29


*/