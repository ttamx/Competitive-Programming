#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

struct SuffixMin{
    map<int,int> dat;
    void insert(int i,int v){
        auto it=dat.lower_bound(i);
        if(it!=dat.end()&&it->second<=v)return;
        it=dat.insert(it,{i,v});
        it->second=v;
        while(it!=dat.begin()&&prev(it)->second>=v)dat.erase(prev(it));
    }
    int query(int i){
        auto it=dat.lower_bound(i);
        return it==dat.end()?INF:it->second;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k,p;
    cin >> n >> m >> k >> p;
    vector<tuple<int,int,int>> in,out;
    for(int i=1;i<=k;i++){
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        in.emplace_back(x1,y1,i);
        out.emplace_back(x2,y2,i);
    }
    out.emplace_back(1,1,0);
    in.emplace_back(n,m,k+1);
    sort(in.begin(),in.end());
    sort(out.begin(),out.end());
    vector<int> dp(k+2,INF);
    for(auto [x,y,i]:in)dp[i]=x+y-2;
    pair<int,int> ans(n+m-2,0);
    for(int c=1;c<=p;c++){
        vector<int> ndp(k+2,INF);
        for(int t=0;t<2;t++){
            for(int tt=0;tt<2;tt++){
                int idx=0;
                SuffixMin ds;
                for(auto [x,y,i]:in){
                    while(idx<=k&&get<0>(out[idx])<=x){
                        auto [xx,yy,j]=out[idx];
                        ds.insert(yy,dp[j]-xx+yy);
                        idx++;
                    }
                    ndp[i]=min(ndp[i],ds.query(y)+x-y);
                }
                for(auto &[x,y,i]:in)y=-y;
                for(auto &[x,y,i]:out)y=-y;
            }
            for(auto &[x,y,i]:in)x=-x;
            for(auto &[x,y,i]:out)x=-x;
            reverse(in.begin(),in.end());
            reverse(out.begin(),out.end());
        }
        dp=move(ndp);
        ans=min(ans,{dp[k+1],c});
    }
    cout << ans.first << " " << ans.second << "\n";
}