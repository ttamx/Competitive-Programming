#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    bool a=false,b=false;
    for(int i=0;i<n;i++){
        int l,r;
        cin >> l >> r;
        if(l==k)a=true;
        if(r==k)b=true;
    }
    cout << (a&&b?"YES":"NO") << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}