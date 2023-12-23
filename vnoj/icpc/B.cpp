#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<bool> b(m);
    bool ans=true;
    for(int i=0;i<n;i++){
        bool c1=false,c2=false;
        for(int j=0;j<m;j++){
            int x;
            cin >> x;
            if(x)c1=true,b[j]=true;
            else c2=true;
        }
        ans&=c1&c2;
    }
    for(auto x:b)ans&=x;
    cout << (ans?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}