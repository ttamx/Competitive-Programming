#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    cin >> s;
    int mn=2e9;
    for(int i=0;i<26;i++){
        char c='a'+i;
        int res=0,cnt=0;
        for(auto x:s){
            if(x==c){
                res=max(res,cnt);
                cnt=0;
            }else{
                cnt++;
            }
        }
        res=max(res,cnt);
        mn=min(mn,res);
    }
    int ans=0;
    while(mn>0){
        ans++;
        mn/=2;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}