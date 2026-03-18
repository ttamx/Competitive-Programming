#include<bits/stdc++.h>

using namespace std;

using PQ = priority_queue<int,vector<int>,greater<int>>;

const int M=1e5+5;
const int S=200;

vector<int> single[M];
vector<pair<int,int>> upd[M];
PQ pq[S][S];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> c(n);
    for(int i=0;i<n;i++){
        int a,b;
        cin >> a >> b >> c[i];
        if(a<S){
            upd[b].emplace_back(a,i);
        }else{
            for(int j=b;j<=m;j+=a){
                single[j].emplace_back(i);
            }
        }
    }
    vector<int> ans(n,-1);
    int last=0;
    for(int i=1;i<=m;i++){
        for(auto [a,j]:upd[i]){
            pq[a][i%a].emplace(j);
        }
        if(i>=last){
            int idx=n;
            for(auto j:single[i]){
                if(ans[j]==-1){
                    idx=min(idx,j);
                }
            }
            for(int j=1;j<S;j++){
                auto &q=pq[j][i%j];
                while(!q.empty()&&ans[q.top()]!=-1){
                    q.pop();
                }
                if(!q.empty()){
                    idx=min(idx,q.top());
                }
            }
            if(idx<n){
                ans[idx]=i;
                last=i+c[idx];
            }
        }
    }
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}