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

const int N=2e5+5;

int n,k;
ll a[N],b[N];

vector<ll> merge(const vector<ll> &a,const vector<ll> &b){
    assert(!a.empty()&&!b.empty());
    int i=1,j=1;
    vector<ll> c{0LL};
    while(i<a.size()||j<b.size()){
        if(j==b.size()||(i<a.size()&&a[i]-a[i-1]>b[j]-b[j-1])){
            c.emplace_back(c.back()+a[i]-a[i-1]);
            i++;
        }else{
            c.emplace_back(c.back()+b[j]-b[j-1]);
            j++;
        }
    }
    return c;
}

void upd(vector<ll> &a,const vector<ll> &b){
    for(int i=0;i<b.size();i++){
        if(a.size()==i){
            a.emplace_back(b[i]);
        }else{
            a[i]=max(a[i],b[i]);
        }
    }
}

vector<vector<vector<ll>>> dnc(int l,int r){
    vector<vector<vector<ll>>> res(k,vector<vector<ll>>(k));
    if(l==r){
        res[0][0]={0LL,b[l]};
        if(k>1)res[1][1]={0LL};
        return res;
    }
    int m=(l+r)/2;
    auto vl=dnc(l,m);
    auto vr=dnc(m+1,r);
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            for(int x=0;x<k;x++){
                if(vl[i][x].empty())continue;
                for(int y=0;y<k;y++){
                    if(vr[y][j].empty())continue;
                    if(x==m-l+1&&y==r-m){
                        upd(res[min(k-1,x+y)][min(k-1,x+y)],merge(vl[i][x],vr[y][j]));
                    }else if(x==m-l+1){
                        upd(res[min(k-1,x+y)][j],merge(vl[i][x],vr[y][j]));
                    }else if(y==r-m){
                        upd(res[i][min(k-1,x+y)],merge(vl[i][x],vr[y][j]));
                    }
                    if(x+y>=k-1){
                        upd(res[i][j],merge(vl[i][x],vr[y][j]));
                    }
                }
            }
        }
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=k;i<=n;i++){
        for(int j=0;j<k;j++){
            b[i]+=a[i-j];
        }
    }
    auto res=dnc(k,n);
    int m=n/k;
    vector<ll> ans(m+1,-LINF);
    for(int x=0;x<k;x++){
        for(int y=0;y<k;y++){
            for(int i=0;i<res[x][y].size();i++){
                ans[i]=max(ans[i],res[x][y][i]);
            }
        }
    }
    for(int i=1;i<=n/k;i++){
        cout << ans[i] << " ";
    }
}