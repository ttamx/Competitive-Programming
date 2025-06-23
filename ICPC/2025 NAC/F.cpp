#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    for(int run=0;run<t;run++){
        if(run)cout << "\n";
        int n,m,u,r,d,l;
        cin >> n >> m >> u >> r >> d >> l;
        if(r<m-1||u<n-1){
            cout << "impossible\n";
            continue;
        }
        vector<string> ans(n,string(m,'*'));
        for(int i=0;i<n;i++){
            for(int j=0;j<m-1;j++){
                if(d){
                    ans[i][j]='D';
                    d--;
                }else if(r){
                    ans[i][j]='R';
                    r--;
                }
            }
        }
        for(int i=1;i<n;i++){
            bool ok=true;
            for(int j=0;j<m;j++){
                if(ans[i][j]=='*'){
                    ans[i][j]='U';
                    u--;
                    ok=true;
                    break;
                }
            }
            assert(ok);
        }
        for(int i=1;i<n;i++){
            for(int j=0;j<m;j++){
                if(ans[i][j]!='*')continue;
                if(u){
                    ans[i][j]='U';
                    u--;
                }else if(l){
                    ans[i][j]='L';
                    l--;
                }
            }
        }
        assert(u==0&&d==0&&l==0&&r==0);
        for(auto x:ans)cout << x << "\n";
    }
}