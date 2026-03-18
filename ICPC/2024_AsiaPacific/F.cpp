#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    ll den=1,num=0;
    vector<bool> bad(n+1);
    auto upd=[&](ll mx,ll mn){
        if(mx*num<=den*mn){
            den=mx;
            num=mn;
        }
    };
    for(int k=2;k<=n;k++){
        if(bad[k])continue;
        for(int i=k*2;i<=n;i+=k)bad[i]=true;
        if(n%k)continue;
        vector<int> b(k);
        for(int i=0;i<n;i++)b[i%k]+=a[i];
        multiset<int> ms;
        for(auto x:b)ms.emplace(x);
        upd(*ms.rbegin(),*ms.begin());
        for(int i=0;i<n-1;i++){
            ms.erase(ms.find(b[i%k]));
            ms.erase(ms.find(b[(i+1)%k]));
            b[i%k]+=a[i+1]-a[0];
            b[(i+1)%k]+=a[0]-a[i+1];
            ms.emplace(b[i%k]);
            ms.emplace(b[(i+1)%k]);
            upd(*ms.rbegin(),*ms.begin());
        }
    }
    ll g=gcd(den,num);
    cout << den/g << " " << num/g << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}