#include<bits/stdc++.h>

using namespace std;

using BS=bitset<1001>;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(n));
    for(int i=0;i<n;i++){
        a[i][n-1]=1;
    }
    vector<BS> c(m);
    for(auto &bs:c){
        int k;
        cin >> k;
        for(int i=0;i<k;i++){
            int x;
            cin >> x;
            x--;
            bs[x]=1;
        }
    }
    for(int mask=1;mask<(1<<m);mask++){
        BS state;
        for(int i=0;i<m;i++){
            if(mask>>i&1){
                state|=c[i];
            }
        }
        int s=state.count();
        int v=(__builtin_popcount(mask)%2==1?-1:1);
        for(int i=0;i<n;i++){
            if(state[i]){
                a[i][n-s]+=v;
            }else{
                a[i][n-s-1]+=v;
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int t=a[i][j]/2;
            a[i][j]-=t*2;
            if(t){
                a[i][j+1]+=t;
            }
            if(a[i][j]<0){
                assert(a[i][j]==-1);
                a[i][j+1]--;
                a[i][j]+=2;
            }
            assert(a[i][j]>=0&&a[i][j]<=1);
        }
    }
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        for(int k=n-1;k>=0;k--){
            if(a[i][k]>a[j][k])return true;
            if(a[i][k]<a[j][k])return false;
        }
        return i<j;
    });
    for(auto x:ord){
        cout << x+1 << " ";
    }
    cout << "\n";
}