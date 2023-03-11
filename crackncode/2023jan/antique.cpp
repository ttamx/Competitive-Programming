#include<bits/stdc++.h>
#include<bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

const bool DBG=false;
const int N=2e5+5;
const int K=1e4+5;

int n,k,A,B;
map<int,int> mp;
gp_hash_table<int,int> mp2;
set<int> num;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> A >> B;
    for(int i=0;i<n;i++){
        int a,b;
        cin >> a >> b;
        mp[b*10+a]=1;
        mp2[b*10+a]=1;
        num.insert(b);
    }
    for(auto [val,cnt]:mp){
        int b=val/10;
        int a=val%10;
        if(DBG)cerr << "factor of " << b << " : ";
        for(auto p:num){
            if(p*p>val)break;
            if(b%p)continue;
            if(DBG)cerr << p << " ";
            for(int i=0;i<10;i++){
                if(mp2[p*10+i]==0)continue;
                for(int j=0;j<10;j++){
                    if(mp2[b/p*10+j]==0)continue;
                    if((i*j)%k!=a)continue;
                    cnt=max(cnt,mp2[p*10+i]+mp2[{b/p*10+j}]);
                }
            }
        }
        if(DBG)cerr << "\n";
        if(DBG)cerr << "count of " << a << " " << b << " : " << cnt << "\n";
        mp2[val]=cnt;
    }
    cout << mp2[B*10+A];
}