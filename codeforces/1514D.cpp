#include<bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    vector<vector<int>> pos(n);
    for(int i=0;i<n;i++){
        pos[a[i]].emplace_back(i);
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        l--,r--;
        int sz=r-l+1;
        int h=(sz+1)/2;
        int f=0;
        for(int t=0;t<30;t++){
            int i=l+rng()%sz;
            int c=upper_bound(pos[a[i]].begin(),pos[a[i]].end(),r)-lower_bound(pos[a[i]].begin(),pos[a[i]].end(),l);
            if(c>h){
                f=c-h;
                break;
            }
        }
        if(f==0){
            cout << 1 << "\n";
            continue;
        }
        if(sz%2==0){
            f--;
            cout << 2+(f+1)/2*2;
        }else{
            cout << 1+(f+1)/2*2;
        }
    }
}