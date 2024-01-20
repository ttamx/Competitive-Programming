#include<bits/stdc++.h>

using namespace std;

const int N=1505;

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
        vector<int> b=a;
        sort(b.begin()+l,b.begin()+r+1);
        for(int j=l;j<=r;j++){
            cout << b[j] << " ";
        }
        cout << "\n";
    }
}