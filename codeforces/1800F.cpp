#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<int,int>> v(n);
    for(auto &[x,y]:v){
        string s;
        cin >> s;
        for(auto c:s)x^=(1<<(c-'a')),y|=(1<<(c-'a'));
    }
    long long ans=0;
    map<int,int> mp[26];
    for(auto [x,y]:v){
        for(int i=0;i<26;i++)if((y&(1<<i))==0)ans+=mp[i][x^((1<<26)-1-(1<<i))];
        for(int i=0;i<26;i++)if((y&(1<<i))==0)mp[i][x]++;
    }
    cout << ans;
}