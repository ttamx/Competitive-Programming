#include<bits/stdc++.h>

using namespace std;

void solve(){
    int n;
    cin >> n;
    string a,b;
    cin >> a >> b;
    auto calc=[&](const string &a,int s){
        int cnt=s;
        for(auto x:a){
            s^=x-'0';
            cnt+=s;
        }
        return cnt;
    };
    int cnt=calc(b,0);
    for(int i=0;i<2;i++){
        int cur=calc(a,i);
        if(cur==cnt){
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}