#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    string s;
    cin >> s;
    string ans=s;
    k--;
    int idx=0;
    while(k--){
        if(idx<ans.size())idx++;
        while(idx<ans.size()&&ans.substr(idx,ans.size()-idx)!=s.substr(0,ans.size()-idx)){
            idx++;
        }
        ans=ans+s.substr(ans.size()-idx,n-ans.size()+idx);
    }
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}