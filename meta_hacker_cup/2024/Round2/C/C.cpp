#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n,m;
    ll k;
    cin >> n >> m >> k;
    vector<vector<int>> a(n,vector<int>(m));
    for(auto &x:a){
        for(auto &y:x){
            cin >> y;
            y--;
        }
    }
    auto check=[&](int s){
        ll res=0;
        for(int i=0;i<n;i++){
            vector<int> cnt(n*m);
            int l=max(0,i-s),r=min(i+s,n-1);
            int all=0;
            for(int j=l;j<=r;j++){
                for(int k=0;k<=min(m-1,s);k++){
                    cnt[a[j][k]]++;
                    all++;
                }
            }
            for(int j=0;j<m;j++){
                if(j-s-1>=0){
                    for(int k=l;k<=r;k++){
                        cnt[a[k][j-s-1]]--;
                        all--;
                    }
                }
                res+=all-cnt[a[i][j]];
                if(j+s+1<m){
                    for(int k=l;k<=r;k++){
                        cnt[a[k][j+s+1]]++;
                        all++;
                    }
                }
            }
        }
        return res;
    };
    int l=1,r=max(n,m);
    while(l<r){
        int mid=(l+r)/2;
        if(check(mid)>=k)r=mid;
        else l=mid+1;
    }
    cout << l << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cerr << "Case #" << i << "\n" << endl;
        cout << "Case #" << i << ": ";
        runcase();
    }
}