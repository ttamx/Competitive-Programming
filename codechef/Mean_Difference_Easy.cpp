#line 2 "D:\\cp-library\\template.hpp"
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
const int INF=INT_MAX/2;
const int MOD=998244353;
const int MOD2=1000000007;
const ll LINF=LLONG_MAX/2;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
#line 2 "D:\\cp-library\\data-structure\\fenwick-tree.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-01-15
 * Description: Fenwick / Binary Indexed Tree
 */

template<class T>
struct Fenwick{
    int n,logn;
    vector<T> t;
    Fenwick(){}
    Fenwick(int _n){init(vector<T>(_n,T{}));}
    template<class U>
    Fenwick(const vector<U> &a){init(a);}
    template<class U>
    void init(const vector<U> &a){
        n=(int)a.size();
        logn=31-__builtin_clz(n);
        t.assign(n+1,T{});
        for(int i=1;i<=n;i++){
            t[i]=t[i]+a[i-1];
            int j=i+(i&-i);
            if(j<=n)t[j]=t[j]+t[i];
        }
    }
    void update(int x,const T &v){
        for(int i=x+1;i<=n;i+=i&-i)t[i]=t[i]+v;
    }
    void update(int l,int r,const T &v){
        update(l,v),update(r+1,-v);
    }
    T query(int x){
        T res{};
        for(int i=x+1;i>0;i-=i&-i)res=res+t[i];
        return res;
    }
    T query(int l,int r){
        return query(r)-query(l-1);
    }
    int find(const T &k){
        int x=0;
        T cur{};
        for(int i=1<<logn;i>0;i>>=1)
            if(x+i<=n&&cur+t[x+i]<=k)x+=i,cur=cur+t[x];
        return x;
    }
};

#line 3 "Mean_Difference_Hard.cpp"

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n);
    vector<pair<ll,int>> vals;
    for(int i=0;i<n;i++){
        cin >> a[i];
        vals.emplace_back(a[i],i);
    }
    if(n==1){
        cout << 0 << "\n";
        return;
    }
    sort(vals.begin(),vals.end());
    for(int i=0;i<n;i++){
        a[vals[i].second]=i;
    }
    vector<ll> ans(n);
    int mn=0,mx=1;
    if(a[mn]>a[mx])swap(mn,mx);
    ll avg=(vals[a[0]].first+vals[a[1]].first)/2;
    ans[1]=max(vals[a[mx]].first-avg,vals[a[mn]].first-avg);
    Fenwick<ll> fsum(n),fcnt(n);
    for(int i=2;i<n;i++){
        if(a[i]>a[mx]){
            fsum.update(a[mx],vals[a[mx]].first);
            fcnt.update(a[mx],1);
            mx=i;
        }else if(a[i]<a[mn]){
            fsum.update(a[mn],vals[a[mn]].first);
            fcnt.update(a[mn],1);
            mn=i;
        }else{
            fsum.update(a[i],vals[a[i]].first);
            fcnt.update(a[i],1);
        }
        {
            ll l=vals[a[mn]].first,r=vals[a[mx]].first;
            while(l<r){
                ll m=(l+r)/2;
                int p=lower_bound(vals.begin(),vals.end(),make_pair(m+1,0))-vals.begin()-1;
                ll sum=vals[a[mn]].first+vals[a[mx]].first+fsum.query(p);
                ll cnt=fcnt.query(p)+2;
                if(sum<(m+1)*cnt)r=m;
                else l=m+1;
            }
            ans[i]=max(ans[i],vals[a[mx]].first-l);
        }
        {
            ll l=vals[a[mn]].first,r=vals[a[mx]].first;
            while(l<r){
                ll m=(l+r+1)/2;
                int p=lower_bound(vals.begin(),vals.end(),make_pair(m,0))-vals.begin();
                ll sum=vals[a[mn]].first+vals[a[mx]].first+fsum.query(p,n-1);
                ll cnt=fcnt.query(p,n-1)+2;
                if(sum>=m*cnt)l=m;
                else r=m-1;
            }
            ans[i]=max(ans[i],l-vals[a[mn]].first);
        }
    }
    cout << ans.back() << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
