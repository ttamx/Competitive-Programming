#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<pair<int,string>> a(n);
    for(auto &[x,y]:a){
        cin >> x >> y;
    }
    sort(a.begin(),a.end());
    string ans="";
    for(int i=0;i<=n;i++){
        auto b=a;
        if(i<n){
            b.erase(b.begin()+i);
        }
        string s="";
        bool ok=true;
        for(auto [x,y]:b){
            int offset=0;
            while(offset<y.size()&&x-1+offset<s.size()&&s[x-1+offset]==y[offset]){
                offset++;
            }
            if(offset==y.size())continue;
            if(s.size()==x-1+offset){
                s+=y.substr(offset,y.size()-offset);
            }else{
                ok=false;
                break;
            }
        }
        if(s.size()==m&&ok){
            if(ans==""){
                ans=s;
            }else if(ans!=s){
                cout << -2;
                exit(0);
            }
        }
    }
    if(ans==""){
        cout << -1;
    }else{
        cout << ans;
    }
}