#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    ll q;
    ll mn=-1e18,mx=1e18;
    cin >> q;
    while(q--){
        ll o;
        cin >> o;
        if(o==1){
            ll a,b,n;
            cin >> a >> b >> n;
            ll lo=(a-b)*(n-1)+b+1;
            ll hi=lo+a-1-b;
            if(n==1)lo=1,hi=a;
            if(lo>mx||hi<mn){
                cout << 0 << ' ';
                continue;
            }
            cout << 1 << ' ';
            mn=max(mn,lo);
            mx=min(mx,hi);
        }else{
            ll a,b;
            cin >> a >> b;
            if(mn==-2e9){
                cout << -1 << ' ';
                continue;
            }
            ll hi=1+max(0ll,(mx-a+a-b-1)/(a-b));
            ll lo=1+max(0ll,(mn-a+a-b-1)/(a-b));
            if(lo==hi){
                cout << lo << ' ';
                continue;
            }
            cout << -1 << ' ';
        }
    }
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll t(1);
    cin >> t;
    while(t--)runcase();
}