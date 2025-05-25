#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;
const int W=1e6+5;
const ll INF=LLONG_MAX/2;

int n;
int w[N];
ll c[N];
ll dp[2][W];

struct Line{
    ll slope,len;
    ll calc_delta(){
        return slope*len;
    }
    bool operator<(const Line &o)const{
        return slope<o.slope||(slope==o.slope&&len<o.len);
    }
};

struct DS{
    ll base,delta;
    ll minw,maxw;
    ll lzmul,lzadd;
    multiset<Line> lines;
    bool rev;
    ll apply(ll x){
        return x*lzmul+lzadd;
    }
    void insert(Line line){
        line.slope=(line.slope-lzadd)*lzmul;
        lines.emplace(line);
    }
    void init(ll w1,ll w2,ll c){
        lzmul=1,lzadd=0;
        rev=false;
        if(w1<w2){
            minw=w1,maxw=w2;
            base=minw*c;
            delta=(maxw-minw)*c;
            insert(Line{c,maxw-minw});
        }else{
            minw=w2,maxw=w2;
            base=w1*c;
            delta=0;
        }
    }
    void update(ll w1,ll w2,ll c){
        ll w=max(w1,w2);
        tie(minw,maxw)=make_pair(w1-maxw,w1-minw);
        if(maxw<0){
            lines.clear();
            delta=0;
            minw=0;
        }else if(minw<0){
            ll cut=-minw;
            assert(!lines.empty());
            auto line=*prev(lines.end());
            lines.erase(prev(lines.end()));
            assert(line.len>=cut);
            line.slope=apply(line.slope);
            delta-=line.slope*cut;
            if(line.len>cut){
                line.len-=cut;
                insert(line);
            }
            minw=0;
        }
        if(!rev){
            for(auto it=lines.end();it!=lines.begin()&&apply((--it)->slope)>c;it=lines.erase(it)){
                auto line=*it;
                delta-=apply(line.slope)*line.len;
                minw+=line.len;
            }
        }else{
            for(auto it=lines.begin();it!=lines.end()&&apply(it->slope)>c;it=lines.erase(it)){
                auto line=*it;
                delta-=apply(line.slope)*line.len;
                minw+=line.len;
            }
        }
        if(maxw<w){
            insert(Line{0LL,w-maxw});
        }
        base+=delta;
        base+=minw*c;
        delta=(w-minw)*c-delta;
        lzmul*=-1;
        lzadd*=-1;
        lzadd+=c;
        maxw=w;
        if(!rev){
            for(auto it=lines.begin();maxw>w2&&it!=lines.end();){
                auto line=*it;
                it=lines.erase(it);
                line.slope=apply(line.slope);
                delta-=line.calc_delta();
                ll used=min(line.len,maxw-w2);
                maxw-=used;
                if(line.len>used){
                    line.len-=used;
                    insert(line);
                    delta+=line.calc_delta();
                    break;
                }
            }
        }else{
            for(auto it=lines.end();maxw>w2&&it!=lines.begin();){
                auto line=*(--it);
                it=lines.erase(it);
                line.slope=apply(line.slope);
                delta-=line.calc_delta();
                ll used=min(line.len,maxw-w2);
                maxw-=used;
                if(line.len>used){
                    line.len-=used;
                    insert(line);
                    delta+=line.calc_delta();
                    break;
                }
            }
        }
        if(maxw>w2){
            assert(lines.empty());
            minw=maxw=w2;
        }
        rev^=true;
    }
    ll query(){
        return base+delta;
    }
}ds;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> w[i];
    }
    for(int i=2;i<=n;i++){
        cin >> c[i];
    }
    ds.init(w[1],w[2],c[2]);
    cout << ds.query() << "\n";
    for(int i=3;i<=n;i++){
        ds.update(w[i-1],w[i],c[i]);
        cout << ds.query() << "\n";
    }
}