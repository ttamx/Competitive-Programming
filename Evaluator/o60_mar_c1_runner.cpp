#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef tuple<ll,ll,ll> t3;

const int N=2005;
const int M=200005;
const int ADD=2;
const int ASK=3;
const int CUT=1;

int n,m;
ll v[N],t[N];
ll p[M],ans[M];
priority_queue<t3,vector<t3>,greater<t3>> pq;

struct line{
    ll m,c;
    line(ll m,ll c):m(m),c(c){}
    ll div(ll x,ll y){
        return x/y+(x%y>0);
    }
    ll isect(line l){
        return div(l.c-c,m-l.m);
    }
    ll get(ll x){
        return m*x+c;
    }
};

vector<pair<line,ll>> lines;
int pos[N];
vector<pair<ll,ll>> isect;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> t[i] >> v[i];
        pq.emplace(t[i],ADD,i);
    }
    for(int i=1;i<=m;i++){
        int b,e;
        cin >> p[i] >> b >> e;
        pq.emplace(b,ASK,-i);
        pq.emplace(e,ASK,i);
    }
    while(!pq.empty()){
        auto [tim,type,id]=pq.top();
        pq.pop();
        if(type==ADD){
            line cur(v[id],-1ll*v[id]*t[id]);
            for(auto [l,i]:lines){
                if(cur.m<=l.m)continue;
                isect.emplace_back(id,i);
                pq.emplace(cur.isect(l),CUT,isect.size()-1);
            }
            pos[id]=lines.size();
            lines.emplace_back(cur,id);
        }else if(type==CUT){
            auto [x,y]=isect[id];
            swap(lines[pos[x]],lines[pos[y]]);
            swap(pos[x],pos[y]);
        }else if(id>0){
            int l=0,r=lines.size();
            while(l<r){
                int mid=(l+r+1)/2;
                if(lines[mid-1].first.get(tim)>=p[id])l=mid;
                else r=mid-1;
            }
            ans[id]+=l;
        }else{
            id=-id;
            int l=0,r=lines.size();
            while(l<r){
                int mid=(l+r+1)/2;
                if(lines[mid-1].first.get(tim)>p[id])l=mid;
                else r=mid-1;
            }
            ans[id]-=l;
        }
    }
    for(int i=1;i<=m;i++)cout << ans[i] << "\n";
}