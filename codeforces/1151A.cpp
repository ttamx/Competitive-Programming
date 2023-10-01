#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    string s;
    cin >> n >> s;
    int ans=2e9;
    auto calc=[&](char x,char y){
        return min((26+x-y)%26,(26+y-x)%26);
    };
    for(int i=3;i<n;i++){
        ans=min(ans,calc('A',s[i-3])+calc('C',s[i-2])+calc('T',s[i-1])+calc('G',s[i]));
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}