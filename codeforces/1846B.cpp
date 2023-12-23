#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s[3];
    for(int i=0;i<3;i++)cin >> s[i];
    for(int i=0;i<3;i++)if(s[i][0]!='.'&&s[i][0]==s[i][1]&&s[i][0]==s[i][2])return void(cout << s[i][0] << "\n");
    for(int i=0;i<3;i++)if(s[0][i]!='.'&&s[0][i]==s[1][i]&&s[0][i]==s[2][i])return void(cout << s[0][i] << "\n");
    if(s[0][0]!='.'&&s[0][0]==s[1][1]&&s[0][0]==s[2][2])return void(cout << s[0][0] << "\n");
    if(s[0][2]!='.'&&s[0][2]==s[1][1]&&s[0][2]==s[2][0])return void(cout << s[0][2] << "\n");
    cout << "DRAW\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}