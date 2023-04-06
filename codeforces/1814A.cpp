#include<bits/stdc++.h>

using namespace std;

void runcase(){
    long long n,k;
    cin >> n >> k;
    if(n%2==1){
        if(k%2==1)cout << "YES\n";
        else cout << "NO\n";
    }else{
        cout << "YES\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}