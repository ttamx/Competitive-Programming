#include<bits/stdc++.h>

using namespace std;

using db = double;

const int N=17;
const int T=105;
const db EPS=1e-9;

int n,m;
int r[N],c[N];
db p[N];
db cnt[T][1<<N];
db solved[T][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<n;i++){
        cin >> r[i] >> c[i] >> p[i];
    }
    cnt[0][0]=1.0;
    for(int t=0;t<m;t++){
        for(int mask=0;mask<1<<n;mask++){
            vector<pair<int,db>> prob;
            db tot=0;
            for(int i=0;i<n;i++){
                if(!(mask>>i&1)){
                    prob.emplace_back(i,solved[t][i]);
                    tot+=solved[t][i];
                }
            }
            if(tot<EPS){
                double q=1.0/(int)prob.size();
                for(auto &[i,x]:prob)x=q;
            }else{
                for(auto &[i,x]:prob)x/=tot;
            }
            for(auto [i,q]:prob){
                if(t+r[i]<=m){
                    db x=cnt[t][mask]*q*(1.0-p[i]);
                    cnt[t+r[i]][mask|(1<<i)]+=x;
                }
                if(t+r[i]+c[i]<=m){
                    db x=cnt[t][mask]*q*p[i];
                    cnt[t+r[i]+c[i]][mask|(1<<i)]+=x;
                    solved[t+r[i]+c[i]][i]+=x;
                }
                
            }
        }
        for(int i=0;i<n;i++){
            solved[t+1][i]+=solved[t][i];
        }
    }
    cout << fixed << setprecision(6);
    for(int i=0;i<n;i++){
        cout << solved[m][i] << "\n";
    }
}