#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

const int P=2001;

struct DS{
    array<int,P> dp;
    DS(){
        dp.fill(0);
    }
    void update(int p,int t){
        for(int i=P-1;i>=p;i--){
            dp[i]=max(dp[i],dp[i-p]+t);
        }
    }
};

struct Stack{
    stack<DS> s;
    Stack():s(){
        s.emplace(DS());
    }
    bool empty(){
        return s.size()==1;
    }
    DS &top(){
        return s.top();
    }
    void pop(){
        assert(s.size()>1);
        s.pop();
    }
    void push(pair<int,int> v){
        DS tmp=s.top();
        tmp.update(v.first,v.second);
        s.emplace(tmp);
    }
};

struct Deque{
    Stack l,r;
    deque<pair<int,int>> dq;
    Deque():l(),r(),dq(){}
    void rebuild(bool left){
        int m=(dq.size()+left)/2;
        while(!l.empty())l.pop();
        while(!r.empty())r.pop();
        for(int i=m-1;i>=0;i--){
            l.push(dq[i]);
        }
        for(int i=m;i<dq.size();i++){
            r.push(dq[i]);
        }
    }
    void push_front(pair<int,int> v){
        l.push(v);
        dq.emplace_front(v);
    }
    void push_back(pair<int,int> v){
        r.push(v);
        dq.emplace_back(v);
    }
    void pop_front(){
        assert(!dq.empty());
        if(l.empty())rebuild(true);
        l.pop();
        dq.pop_front();
    }
    void pop_back(){
        assert(!dq.empty());
        if(r.empty())rebuild(false);
        r.pop();
        dq.pop_back();
    }
    int query(int p){
        int res=0;
        for(int i=0;i<=p;i++){
            res=max(res,l.top().dp[i]+r.top().dp[p-i]);
        }
        return res;
    }
};

void runcase(){
    int q;
    cin >> q;
    vector<int> t(q+1),id(q+1),a(q+1),b(q+1),qr(q+1);
    vector<vector<int>> adj(q+1);
    vector<int> ans;
    id[0]=0;
    int cur_id=1;
    for(int i=1;i<=q;i++){
        int x;
        cin >> t[i] >> x;
        x--;
        assert(x<cur_id);
        adj[id[x]].emplace_back(i);
        if(t[i]==1){
            id[cur_id++]=i;
        }else{
            if(t[i]==2){
                cin >> a[i] >> b[i];
            }else if(t[i]==4){
                cin >> a[i];
                qr[i]=ans.size();
                ans.emplace_back(0);
            }
            id[x]=i;
        }
    }
    Deque ds;
    function<void(int)> dfs=[&](int u){
        pair<int,int> memo;
        if(t[u]==2){
            ds.push_back(make_pair(a[u],b[u]));
        }else if(t[u]==3){
            memo=ds.dq.front();
            ds.pop_front();
        }else if(t[u]==4){
            ans[qr[u]]=ds.query(a[u]);
        }
        for(auto v:adj[u]){
            dfs(v);
        }
        if(t[u]==2){
            ds.pop_back();
        }else if(t[u]==3){
            ds.push_front(memo);
        }
    };
    dfs(0);
    for(auto x:ans){
        cout << x << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}