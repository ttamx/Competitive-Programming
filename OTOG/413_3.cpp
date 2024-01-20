#include<bits/stdc++.h>

using namespace std;

int n,q;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        vector<int> b;
        for(int j=l;j<=r;j++){
            b.push_back(a[j]);
        }
        sort(b.begin(),b.end());
        for(auto j:b){
            cout << j << " ";
        }
        cout << "\n";
    }
}