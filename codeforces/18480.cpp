#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    int x,y;
    cin >> x >> y;
    bool ok=true;
    for(int i=0;i<k;i++){
        int a,b;
        cin >> a >> b;
        if((a+b)%2==(x+y)%2)ok=false;
    }
    cout << (ok?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}