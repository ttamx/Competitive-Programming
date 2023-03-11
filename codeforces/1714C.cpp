#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    string ans="";
    int num=9;
    while(n>0){
        ans=to_string(min(n,num))+ans;
        n-=min(n,num);
        num--;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}