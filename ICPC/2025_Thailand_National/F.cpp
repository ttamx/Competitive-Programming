#include<bits/stdc++.h>

using namespace std;

const int M=1e5+5;
const int S=320;

vector<pair<int,int>> ds[M];
priority_queue<int,vector<int>,greater<int>> pq[S][S];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> c(n);
    for(int i=0;i<n;i++){
        int a,b;
        cin >> a >> b >> c[i];
        ds[b].emplace_back(a,i);
    }
    vector<int> ans(n,-1);
    int last=0;
    for(int i=1;i<=m;i++){
        int idx=n;
        for(auto [a,j]:ds[i]){
            if(a<S){
                pq[a][i%a].emplace(j);
            }else if(ans[j]==-1){
                idx=min(idx,j);
                if(i+a<=m){
                    ds[i+a].emplace_back(a,j);
                }
            }
        }
        vector<pair<int,int>>().swap(ds[i]);
        if(i>=last){
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