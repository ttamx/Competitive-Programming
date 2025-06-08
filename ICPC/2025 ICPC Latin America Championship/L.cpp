#include<bits/stdc++.h>

using namespace std;

string s[10]={
    "GGGgGGG",
    "gggggGG",
    "gGGGGGg",
    "ggGGGGG",
    "GggGgGG",
    "GgGGGgG",
    "GGGGGgG",
    "ggGggGG",
    "GGGGGGG",
    "GgGGGGG"
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        string t;
        cin >> t;
        int cur=0;
        for(auto x:t)cur+=x=='g'||x=='G';
        char c='X';
        for(int d=0;d<10;d++){
            int cnt=0;
            for(int j=0;j<7;j++){
                if(t[j]==s[d][j])cnt++;
            }
            if(cnt==cur){
                if(c=='X')c=char('0'+d);
                else c='*';
            }
        }
        cout << c;
    }
}