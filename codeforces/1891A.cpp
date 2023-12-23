#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    int l=1,r=1;
    while(l<=n){
        for(int i=l+1;i<=r;i++){
            if(a[i]<a[i-1])return void(cout << "NO\n");
        }
        l=r+1;
        r=min(r*2,n);
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}