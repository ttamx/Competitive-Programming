#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    cin >> s;
    int n=s.size();
    int ans=1;
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            bool ok=true;
            for(int x=0;x<=j-i;x++){
                if(s[i+x]!=s[j-x])ok=false;
            }
            if(ok)ans=max(ans,j-i+1);
        }
    }
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}