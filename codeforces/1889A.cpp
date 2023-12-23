#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    string s;
    cin >> n >> s;
    vector<int> cnt(2);
    for(auto x:s)cnt[x-'0']++;
    if(cnt[0]!=cnt[1])return void(cout << "-1\n");
    vector<int> ans;
    for(int l=0,r=n-1;l<r;l++,r--){
        if(s[l]!=s[r])continue;
        if(s[l]=='0'){
            s=s.substr(0,r+1)+"01"+s.substr(r+1,s.size()-r-1);
            ans.emplace_back(r+1);
            r+=2;
        }else{
            s=s.substr(0,l)+"01"+s.substr(l,s.size()-l);
            ans.emplace_back(l);
            r+=2;
        }
    }
    cout << ans.size() << "\n";
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}