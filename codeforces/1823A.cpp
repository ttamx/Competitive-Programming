#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    for(int i=0;i<=n;i++){
        if(i*(i-1)/2+(n-i)*(n-i-1)/2==k){
            cout << "YES\n";
            for(int j=0;j<i;j++)cout << "-1 ";
            for(int j=0;j<n-i;j++)cout << "1 ";
            cout << "\n";
            return;
        }
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}