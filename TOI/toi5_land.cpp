#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<double>> a(n,vector<double>(m));
    for(auto &x:a)for(auto &y:x)cin >> y;
    vector<int> ord(n*m);
    iota(ord.begin(),ord.end(),0);
    double ans=numeric_limits<double>::max();
    do{
        auto b=a;
        vector<vector<bool>> used(n,vector<bool>(m));
        auto add=[&](int i,int j,double v){
            if(i<0||i>=n||j<0||j>=m||used[i][j])return;
            b[i][j]+=v;
        };
        double res=0;
        for(auto idx:ord){
            int i=idx/m,j=idx%m;
            res+=b[i][j];
            used[i][j]=true;
            for(int di=-1;di<=1;di++){
                for(int dj=-1;dj<=1;dj++){
                    add(i+di,j+dj,b[i][j]/10);
                }
            }
        }
        ans=min(ans,res);
    }while(next_permutation(ord.begin(),ord.end()));
    cout << fixed << setprecision(2) << ans;
}