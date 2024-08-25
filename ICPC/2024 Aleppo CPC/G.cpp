#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<vector<int>> a(n,vector<int>(1000));
    int rem=0;
    vector<tuple<int,int,int>> qr(q);
    for(auto &[x,l,r]:qr){
        cin >> x >> l >> r;
        x--,l--,r--;
        for(int i=l;i<=r;i++){
            a[x][i]++;
        }
    }
    int cnt=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<1000;j++){
            if(a[i][j]>1){
                cnt++;
            }
        }
    }
    if(cnt==0){
        return void(cout << "YES\n");
    }
    for(auto &[x,l,r]:qr){
        int cnt2=0;
        for(int i=l;i<=r;i++){
            if(a[x][i]==2){
                cnt2++;
            }
        }
        if(cnt==cnt2){
            return void(cout << "YES\n");
        }
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}