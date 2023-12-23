#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(202,2e9);
    for(int i=0;i<n;i++){
        int d,t;
        cin >> d >> t;
        a[d]=min(a[d],t);
    }
    int k=2e9;
    for(int i=1;i<=min(200,k);i++)k=min(k,i+(a[i]-1)/2);
    cout << k << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}