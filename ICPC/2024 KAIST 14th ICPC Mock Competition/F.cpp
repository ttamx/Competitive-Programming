#include<bits/stdc++.h>

using namespace std;

void solve(){
    int n;
    cin >> n;
    int sum=0;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        if(i==0)continue;
        if(s=="111"){
            sum^=2;
        }else if(s[1]=='1'&&(s[0]=='1'||s[2]=='1')){
            sum^=1;
        }
    }
    cout << (sum?"Yesyes":"Nono") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}