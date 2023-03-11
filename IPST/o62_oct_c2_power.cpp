#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

typedef pair<int,int> p2;

int n,m,ans;
int dp[N];
set<int> s;
queue<p2> q;

int calc(int x){
    if(s.empty())return 0;
    auto it=s.lower_bound(x);
    if(it==s.end()){
        int l=*(--it);
        int tmp=max(0,dp[l]-(x-l));
        //printf("input: %d\tl: %d\t\treturn: %d\n",x,l,tmp);
        return tmp;
    }
    if(it==s.begin()){
        int r=*it;
        int tmp=max(0,dp[r]-(r-x));
        //printf("input: %d\t\tr: %d\treturn: %d\n",x,r,tmp);
        return tmp;
    }
    int r=*it,l=*(--it);
    int tmp=max({0,dp[l]-(x-l),dp[r]-(r-x)});
    //printf("input: %d\tl: %d\tr: %d\treturn: %d\n",x,l,r,tmp);
    return tmp;
}

void sol(int x,int y,int z){
        int cost=z+calc(x);
        ans=max(ans,cost);
        if(cost>calc(y)){
            q.emplace(y,cost);
            auto IT=s.lower_bound(y);
            if(IT!=s.begin()){
                auto it=IT;
                --it;
                while(true){
                    if(cost-(y-*it)>dp[*it])it=s.erase(it);
                    else break;
                    if(it==s.begin())break;
                    --it;
                }
            }
            if(IT!=s.end()){
            auto it=IT;
                ++it;
                while(it!=s.end()){
                    if(cost-(*it-y)>dp[*it])it=s.erase(it);
                    else break;
                }
            }
        }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    while(m--){
        int x,y,z;
        cin >> x >> y >> z;
        sol(x,y,z);
        sol(y,x,z);
        while(!q.empty()){
            auto [i,v]=q.front();
            s.insert(i);
            dp[i]=max(dp[i],v);
            q.pop();
        }
        cout << ans << '\n';
    }
}
