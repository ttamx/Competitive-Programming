#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n,m;
    cin >> n >> m;
    if(n<m){
        cout << "NO\n";
    }else if(n<=m*2-2){
        cout << "YES\n";
    }else if((n-(m*2-2))%2==0){
        cout << "YES\n";
    }else{
        cout << "NO\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}