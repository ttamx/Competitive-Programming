#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

struct Event{
    int t,type,val;
    Event(int _t,int _type,int _val):t(_t),type(_type),val(_val){}
    bool operator<(const Event &o)const{
        return t>o.t||(t==o.t&&type>o.type);
    }
};

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    priority_queue<Event> event;
    for(int i=0;i<n;i++){
        int d,a;
        cin >> d >> a;
        event.emplace(d,1,a);
    }
    deque<pair<int,int>> milk;
    ll ans=0;
    int last=-1;
    while(!event.empty()){
        auto e=event.top();
        event.pop();
        // cerr << "E : " << e.t << " " << e.type << "\n";
        if(!milk.empty()){
            // cerr << "CONSUME " << last << " TO " << e.t-1 << "\n";
            ll to_consume=1LL*(e.t-last)*m;
            ll consumed=0;
            // cerr << "TO CONSUMED " << to_consume  << "\n";
            // cerr << "BEFORE : ";
            // for(auto [x,y]:milk) cerr << "(" << x << "," << y << ") ";
            // cerr << "\n";
            while(!milk.empty()&&to_consume>0){
                ll used=min((ll)milk.back().second,to_consume);
                milk.back().second-=used;
                to_consume-=used;
                consumed+=used;
                if(milk.back().second==0){
                    milk.pop_back();
                }
            }
            // cerr << "AFTER : ";
            // for(auto [x,y]:milk) cerr << "(" << x << "," << y << ") ";
            // cerr << "\n";
            // cerr << "CONSUMED " << consumed  << "\n";
            ans+=consumed/m;
        }
        if(e.type==0){
            if(!milk.empty()&&milk.front().first==e.t-k){
                // cerr << "DELETE" << milk.front().first << "\n";
                milk.pop_front();
            }
        }
        if(e.type==1){
            milk.emplace_back(e.t,e.val);
            event.emplace(e.t+k,0,e.val);
        }
        last=e.t;
    }
    // cerr << "----\n";
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}