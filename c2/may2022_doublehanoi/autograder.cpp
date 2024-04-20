#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;

const ll INF=LLONG_MAX/2;

static int N;
static std::vector<int> S0,S1,S2;
static std::vector<int> T0,T1,T2;

namespace SUB1{
    ll hanoi(int n,vi s0,vi s1,vi s2,vi t0,vi t1,vi t2){
        vector<vi> s{s0,s1,s2},t{t0,t1,t2};
        for(auto &v:s)reverse(v.begin(),v.end());
        for(auto &v:t)reverse(v.begin(),v.end());
        queue<pair<int,vector<vi>>> q;
        map<vector<vi>,bool> vis;
        map<vector<vi>,vector<vi>> par;
        q.emplace(0,s);
        vis[s]=true;
        while(!q.empty()){
            auto [d,u]=q.front();
            q.pop();
            if(u==t){
                // vector<vector<vi>> path;
                // for(;!u.empty();u=par[u])path.emplace_back(u);
                // reverse(path.begin(),path.end());
                // for(auto a:path){
                //     for(auto v:a){
                //         for(auto x:v)cerr << x << " ";
                //         cerr << "\n";
                //     }
                //     cerr << "\nV V V\n\n";
                // }
                return d;
            }
            auto p=u;
            for(int i=0;i<3;i++)if(!u[i].empty()){
                for(int j=0;j<3;j++)if(i!=j){
                    if(!u[j].empty()&&u[i].back()>u[j].back())continue;
                    u[j].emplace_back(u[i].back());
                    u[i].pop_back();
                    if(!vis[u]){
                        par[u]=p;
                        vis[u]=true;
                        q.emplace(d+1,u);
                    }
                    u[i].emplace_back(u[j].back());
                    u[j].pop_back();
                }
            }
        }
        assert(false);
        return 0LL;
    }
}

namespace SOL{
vector<vl> calc_dp(int n,vector<vi> a){
	for(auto &v:a)reverse(v.begin(),v.end());
	vi cnt(3);
	auto push=[&](int x){
		for(int i=0;i<3;i++){
			cnt[i]=0;
			while(!a[i].empty()&&a[i].back()<=x){
				cnt[i]++;
				a[i].pop_back();
			}
		}
	};
	vector<vl> dp(n+1,vl(3));
	for(int k=1;k<=n;k++){
		push(k-1);
		for(int i=0;i<3;i++){
			if(cnt[i]==2){
				dp[k][i]=dp[k-1][i];
				continue;
			}
			if(cnt[i]==0){
				dp[k][i]=INF;
				for(int j=0;j<3;j++)if(i!=j){
					if(cnt[j]==1){
						dp[k][i]=min(dp[k][i],dp[k-1][j]+(2LL<<k)-2);
						dp[k][i]=min(dp[k][i],dp[k-1][i]+(2LL<<k)-1);
					}
					if(cnt[j]==0)dp[k][i]=dp[k-1][j]+(1LL<<k);
				}
				continue;
			}
			for(int j=0;j<3;j++)if(cnt[j]==0){
				dp[k][i]=dp[k-1][j]+(1LL<<k)-1;
			}
		}
	}
	return dp;
}

struct State{
	ll d;
	vi u;
	int x;
	State(ll _d,vi _u,int _x):d(_d),u(_u),x(_x){}
	bool operator<(const State &o)const{
		return d>o.d;
	}
};

ll hanoi(int n,vi s0,vi s1,vi s2,vi t0,vi t1,vi t2){
	vector<vi> s{s0,s1,s2},t{t0,t1,t2};
	auto dps=calc_dp(n,s);
	auto dpt=calc_dp(n,t);
	for(int k=n-1;k>=0;k--){
		vi cs(3),ct(3),ps,pt;
		bool ok=true;
		for(int i=0;i<3;i++){
			while(!s[i].empty()&&s[i].back()==k){
				cs[i]++;
				s[i].pop_back();
			}
			while(!t[i].empty()&&t[i].back()==k){
				ct[i]++;
				t[i].pop_back();
			}
			if(cs[i]!=ct[i])ok=false;
		}
		if(ok)continue;
		ll ans=INF;
		map<pair<vi,int>,ll> dp;
		priority_queue<State> pq;
		for(int i=0;i<3;i++){
			pq.emplace(State(dps[k][i],cs,i));
			dp[{cs,i}]=dps[k][i];
		}
		while(!pq.empty()){
			auto [d,u,x]=pq.top();
			pq.pop();
			if(d>dp[{u,x}])continue;
			if(u==ct){
				ans=min(ans,d+dpt[k][x]);
				continue;
			}
			for(int i=0;i<3;i++)if(i!=x&&u[i]>0){
				for(int j=0;j<3;j++)if(i!=j&&j!=x){
					u[i]--,u[j]++;
					for(int p=0;p<3;p++){
						ll nd=d+1;
						if(p!=x)nd+=(2LL<<k)-2;
						if(dp.find({u,p})==dp.end()||nd<dp[{u,p}]){
							dp[{u,p}]=nd;
							pq.emplace(State(nd,u,p));
						}
					}
					u[i]++,u[j]--;
				}
			}
		}
		return ans;
	}
	return 0LL;
}
}

int main()
{
    int t=0;
    while(true){
        t++;
        if(t%100==0){
            cout << "TEST " << t << "\n";
        }
        int n=3;
        vector<vi> s(3),t(3);
        for(int i=0;i<n;i++){
            for(int j=0;j<2;j++){
                int x=rand()%3;
                s[x].emplace_back(i);
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<2;j++){
                int x=rand()%3;
                t[x].emplace_back(i);
            }
        }
        int a=SUB1::hanoi(n,s[0],s[1],s[2],t[0],t[1],t[2]);
        int b=SOL::hanoi(n,s[0],s[1],s[2],t[0],t[1],t[2]);
        if(a!=b){
            cout << "Expected " << a << " found " << b << "\n";
            cout << n << "\n";
            for(int i=0;i<3;i++){
                cout << s[i].size();
                for(auto x:s[i])cout << " " << x;
                cout << "\n";
            }
            for(int i=0;i<3;i++){
                cout << t[i].size();
                for(auto x:t[i])cout << " " << x;
                cout << "\n";
            }
            break;
        }
    }
}