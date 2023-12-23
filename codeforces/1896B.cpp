#include<bits/stdc++.h>

using namespace std;

const int inf=1e9;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    int l=0,r=n-1;
    while(l<=r&&s[l]=='B')l++;
    while(l<=r&&s[r]=='A')r--;
    int ans=r-l;
    cout << max(ans,0) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}