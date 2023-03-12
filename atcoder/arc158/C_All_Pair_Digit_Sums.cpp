#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n);
    vector<int> v[15];
    for(auto &x:a){
        cin >> x;
        ll num=x;
        int dig=0;
        while(num>0){
            v[dig].emplace_back(num%10);
            num/=10;
            dig++;
        }
    }
    ll ans=0;
    for(int i=0;i<15;i++)for(auto x:v[i])ans+=x;
    ans*=n;
    for(int i=0;i<15;i++)sort(v[i].begin(),v[i].end());
    for(auto &x:a){
        cin >> x;
        ll num=x;
        int dig=0;
        while(num>0){
            int idx=lower_bound(v[dig].begin(),v[dig].end(),10-(num%10))-v[dig].begin();
            ans-=9*(v[dig].size()-idx);
            ans+=n*(num%10);
            num/=10;
            dig++;
        }
    }
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}