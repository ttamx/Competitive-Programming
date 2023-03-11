#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    int ans=0;
    for(int i=0;i<n;++i){
        int x;
        cin >> x;
        ans|=x;
    }
    if(ans)cout << "YES\n";
    else cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();   
}