#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    int l=1,r=n;
    for(int i=1;i<=n;i++){
        cout << (i%2==1?r--:l++) << " \n"[i==n];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}