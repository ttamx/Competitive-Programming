#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        ll a,b,x;
        cin >> a >> b >> x;
        set<pair<int,int>> vis;
        function<bool(ll,ll)> rec=[&](ll a,ll b)->bool {
            if(a<b)swap(a,b);
            if(a==x||b==x)return true;
            if(x>a)return false;
            if(b==0)return false;
            if(x%b==a%b)return true;
            return rec(a%b,b);
        };
        cout << (rec(a,b)?"YES":"NO") << "\n";
    }
}