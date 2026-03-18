#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void solve(){
    auto ask=[&](int a,int b){
        cout << "? " << a << " " << b << endl;
        int res;
        cin >> res;
        return res;
    };
    int ans=0;
    for(int i=0;i<30;i++){
        int v=1<<i;
        if(ask(v-ans,3*v-ans)==2*v){
            ans+=v;
        }
    }
    cout << "! " << ans << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}