#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s[2];
    cin >> s[0] >> s[1];
    int n,q;
    cin >> n >> q;
    int cnt=0;
    for(int i=0;i<s[0].size();i++)cnt+=(s[0][i]!=s[1][i]);
    map<int,vector<int>> mp;
    for(int i=1;i<=q;i++){
        for(auto x:mp[i])cnt+=(s[0][x]!=s[1][x]);
        int t;
        cin >> t;
        if(t==1){
            int x;
            cin >> x;
            x--;
            cnt-=(s[0][x]!=s[1][x]);
            mp[i+n].emplace_back(x);
        }else if(t==2){
            int a,b,c,d;
            cin >> a >> b >> c >> d;
            a--,b--,c--,d--;
            cnt-=(s[a][b]!=s[a^1][b]);
            if(b!=d)cnt-=(s[c][d]!=s[c^1][d]);
            swap(s[a][b],s[c][d]);
            cnt+=(s[a][b]!=s[a^1][b]);
            if(b!=d)cnt+=(s[c][d]!=s[c^1][d]);
        }else{
            cout << (cnt==0?"YES":"NO") << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}