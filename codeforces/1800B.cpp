#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    string s;
    cin >> n >> k >> s;
    int cnt[2][26]={};
    int ans=0;
    for(auto x:s){
        if(isupper(x)){
            if(cnt[0][tolower(x)-'a']){
                cnt[0][tolower(x)-'a']--;
                ans++;
            }else{
                cnt[1][x-'A']++;
            }
        }else{
            if(cnt[1][toupper(x)-'A']){
                cnt[1][toupper(x)-'A']--;
                ans++;
            }else{
                cnt[0][x-'a']++;
            }
        }
    }
    for(int i=0;i<2;i++){
        for(int j=0;j<26;j++){
            while(k>0&&cnt[i][j]>1){
                cnt[i][j]-=2;
                ans++;
                k--;
            }
        }
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}