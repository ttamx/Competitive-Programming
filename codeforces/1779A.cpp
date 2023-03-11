#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    int l=0;
    for(auto x:s)if(x=='L')l++;
    if(l==0||l==n){
        cout << -1 << '\n';
        return;
    }
    int ans=0;
    for(int i=0;i<n-1;i++)if(s.substr(i,2)=="LR")ans=i+1;
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}