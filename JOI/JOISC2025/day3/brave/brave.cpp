#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = pair<ll,int>;

const int N=6005;

int n,ml,q;
ll t;
ll s[N],h[N],p[N];
ll rv[N];
int nxt[N];
bool merged[N];
vector<int> ord;

vector<ll> pts;

set<pair<ll,int>> heads;
priority_queue<P,vector<P>,greater<P>> event;

struct Info{
    ll pos,tot,lv,tot_cnt,ext,tot_pen,cur_pen;
    ll cnt[N];
    bool has[N];
    void init(int i){
        pos=s[i];
        tot=h[i];
        lv=0;
        tot_cnt=0;
        ext=0;
        cnt[i]=0;
        has[i]=true;
        tot_pen=p[i]*h[i];
        cur_pen=0;
    }
    void extend(ll tar){
        assert(tar>=lv);
        ll v=tar-lv;
        pos+=v*tot;
        ext+=v*tot;
        tot_cnt+=v*tot;
        cur_pen+=tot_pen*v;
        for(int i=1;i<=n;i++){
            if(has[i]){
                cnt[i]+=h[i]*v;
            }
        }
        lv=tar;
    }
    void shrink(ll v){
        assert(v>=0);
        tot_cnt-=v;
        for(auto i:ord){
            if(v<=cnt[i]){
                cerr << "REMOVE " << p[i] << " BY " << v << "\n";
                cnt[i]-=v;
                cur_pen-=p[i]*v;
                v=0;
                break;
            }else{
                cerr << "REMOVE " << p[i] << " BY " << cnt[i] << "\n";
                cur_pen-=p[i]*cnt[i];
                v-=cnt[i];
                cnt[i]=0;
            }
        }
        assert(v==0);
    }
    void merge(const Info &o){
        tot+=o.tot;
        ext+=o.ext;
        pos+=o.ext;
        tot_cnt+=o.tot_cnt;
        tot_pen+=o.tot_pen;
        cur_pen+=o.cur_pen;
        for(int i=1;i<=n;i++){
            assert(!has[i]||!o.has[i]);
            has[i]|=o.has[i];
            cnt[i]+=o.cnt[i];
        }
    }
    void copy(const Info &o){
        pos=o.pos;
        tot=o.tot;
        lv=o.lv;
        tot_cnt=o.tot_cnt;
        ext=o.ext;
        tot_pen=o.tot_pen;
        cur_pen=o.cur_pen;
        for(int i=1;i<=n;i++){
            cnt[i]=o.cnt[i];
            has[i]=o.has[i];
        }
    }
    ll calc(ll tar){
        assert(lv<=tar);
        return cur_pen+tot_pen*(lv-tar);
    }
}dat[N],memo[N];

int buf;
ll lv[N];

void calc_next(int i){
    ll cur=dat[i].pos;
    ll tot=dat[i].tot;
    ll cur_lv=dat[i].lv;
    auto it=heads.upper_bound(make_pair(s[i],i));
    assert(it!=heads.end());
    auto [tar,j]=*it;
    assert(i!=j);
    ll dif=max(tar-cur,0LL);
    ll step=(dif+tot-1)/tot;
    nxt[i]=j;
    event.emplace(cur_lv+step,i);
}

void process(){
    while(!event.empty()){
        auto [cur,i]=event.top();
        event.pop();
        if(cur>ml)break;
        if(merged[i])continue;
        int j=nxt[i];
        dat[i].extend(cur);
        dat[j].extend(cur);
        ll overlap=dat[i].pos-s[j];
        cerr << "AT " << cur << " MERGE " << i << " " << j << "\n";
        cerr << dat[i].pos << " " << s[j] << "\n";
        assert(overlap>=0);
        dat[i].shrink(dat[i].tot_cnt-overlap);
        dat[i].merge(dat[j]);
        cerr << "NEW POS " << dat[i].pos << "\n";
        cerr << "TOT CNT " << dat[i].tot_cnt << "\n";
        cerr << "CUR PEN " << dat[i].cur_pen << "\n";
        merged[j]=true;
        heads.erase(make_pair(s[j],j));
        if(heads.rbegin()->second==i){
            assert(dat[i].pos>=t);
            cerr << "SAVE AT " << cur << " " << dat[i].pos << " " << dat[i].tot_cnt << "\n";
            dat[i].shrink(dat[i].tot_cnt-(dat[i].pos-t));
            assert(dat[i].tot_cnt==(dat[i].pos-t));
            if(lv[buf]!=cur){
                assert(lv[buf]<cur);
                buf++;
                lv[buf]=cur;
            }
            memo[buf].copy(dat[i]);
        }else{
            calc_next(i);
        }
        cerr << "  MERGED " << dat[i].cur_pen << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> ml >> t;
    for(int i=1;i<=n;i++){
        cin >> s[i] >> h[i] >> p[i];
        heads.emplace(s[i],i);
        ord.emplace_back(i);
        dat[i].init(i);
    }
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return p[i]>p[j];
    });
    for(auto i:ord){
        cerr << i << " ";
    }
    cerr << "\n";
    s[n+1]=t;
    heads.emplace(t,n+1);
    for(int i=1;i<=n;i++){
        calc_next(i);
    }
    lv[0]=-1;
    process();
    for(int i=1;i<=buf;i++){
        cerr << lv[i] << " " << memo[i].cur_pen << " " << memo[i].tot_pen << " , ";
    }
    lv[buf+1]=ml+1;
    cin >> q;
    while(q--){
        ll k;
        cin >> k;
        int l=0,r=buf;
        while(l<r){
            int m=(l+r+1)/2;
            if(memo[m].cur_pen<=k)l=m;
            else r=m-1;
        }
        ll ans=lv[l];
        ll dif=k-memo[l].cur_pen;
        assert(dif>=0);
        if(memo[l].tot_pen>0){
            ans+=dif/memo[l].tot_pen;
        }else{
            ans=ml;
        }
        cout << min(ans,lv[l+1]-1) << "\n";
    }
}