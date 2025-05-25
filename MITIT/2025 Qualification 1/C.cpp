#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    int v1=1,v2=2;
    vector<pair<int,int>> ans;
    for(auto c:s){
        if(c=='O'){
            if(v1>2*n||v2>2*n)return void(cout << "NO\n");
            ans.emplace_back(v1,v2);
            v1+=2,v2+=2;
        }else if(v1<v2&&v1+2<=2*n){
            ans.emplace_back(v1,v1+2);
            v1+=4;
        }else if(v2<v1&&v2+2<=2*n){
            ans.emplace_back(v2,v2+2);
            v2+=4;
        }else{
            cout << "NO\n";
            return;
        }
    }
    int last=0;
    cout << "YES\n";
    for(auto [u,v]:ans){
        cout << u << " " << v << "\n";
        assert(u+v>=last);
        last=u+v;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}