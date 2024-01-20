#include<bits/stdc++.h>

using namespace std;

const int N=1505;

int n,q;
int a[N],b[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        for(int j=0;j<n;j++){
            b[j]=a[j];
        }
        sort(b+l,b+r+1);
        for(int j=l;j<=r;j++){
            cout << b[j] << " ";
        }
        cout << "\n";
    }
}