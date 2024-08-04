#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using i128 = __int128_t;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string a,b;
    cin >> a >> b;
    ll c,d;
    cin >> c >> d;
    int n=a.size();
    map<array<int,10>,set<i128>> s;
    for(int i=0;i<(1<<n)-1;i++){
        array<int,10> cnt;
        for(int i=0;i<10;i++)cnt[i]=0;
        string t="";
        for(int j=0;j<n;j++){
            if(i>>j&1){
                cnt[a[j]-'0']++;
            }else{
                t+=a[j];
            }
        }
        s[cnt].emplace(i128(stoll(t))*d);
    }
    int m=b.size();
    for(int i=0;i<(1<<m)-1;i++){
        array<int,10> cnt;
        for(int i=0;i<10;i++)cnt[i]=0;
        string t="";
        for(int j=0;j<m;j++){
            if(i>>j&1){
                cnt[b[j]-'0']++;
            }else{
                t+=b[j];
            }
        }
        ll x=stoll(t);
        auto it=s[cnt].find(i128(x)*c);
        if(it!=s[cnt].end()){
            cout << "possible\n";
            cout << ll(*it/d) << " " << x << "\n";
            exit(0);
        }
    }
    cout << "impossible";
}