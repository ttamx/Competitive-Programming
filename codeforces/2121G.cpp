#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> qs[2];
    qs[0].assign(n+1,0);
    qs[1].assign(n+1,0);
    for(int i=0;i<n;i++){
        qs[0][i+1]=qs[0][i]+(s[i]=='0');
        qs[1][i+1]=qs[1][i]+(s[i]=='1');
    }
    ll ans=0;
    {
        vector<int> ord(n+1);
        iota(ord.begin(),ord.end(),0);
        sort(ord.begin(),ord.end(),[&](int i,int j){
            return make_pair(qs[1][i]-qs[0][i],i)<make_pair(qs[1][j]-qs[0][j],j);
        });
        Fenwick<ll> fcnt(n+1),fsum(n+1);
        for(auto i:ord){
            ans+=fcnt.query(i)*qs[1][i]-fsum.query(i);
            fcnt.update(i,+1);
            fsum.update(i,qs[1][i]);
        }
    }
    {
        vector<int> ord(n+1);
        iota(ord.begin(),ord.end(),0);
        sort(ord.begin(),ord.end(),[&](int i,int j){
            return make_pair(qs[0][i]-qs[1][i],-i)<make_pair(qs[0][j]-qs[1][j],-j);
        });
        Fenwick<ll> fcnt(n+1),fsum(n+1);
        for(auto i:ord){
            ans+=fcnt.query(i)*qs[0][i]-fsum.query(i);
            fcnt.update(i,+1);
            fsum.update(i,qs[0][i]);
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