#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int n,m;
map<ll,int> s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    s[0]=0;
    for(int i=1;i<=n;i++){
        ll a;
        cin >> a;
        a-=1LL*m*i;
        auto it=s.lower_bound(a);
        if(it==s.end())continue;
        int val=it->second-1;
        s[a]=val;
        it=s.find(a);
        while(it!=s.begin()&&(--it)->second>=val)it=s.erase(it);
    }
    cout << s.begin()->second+n;
}