#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<ll>> a(n,vector<ll>(m));
    for(int sz=1,bt=1;sz<=max(n,m);sz*=2){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(i&sz)a[i][j]+=sz*sz;
                if(j&sz)a[i][j]+=sz*sz*2;
            }
        }
    }
    cout << n*m << '\n';
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}