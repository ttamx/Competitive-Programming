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

template<int N>
void solve(int n){
    if(N<=n)return solve<min(N*2,int(5e5+5))>(n);
    vector<int> a(2*n);
    for(auto &x:a)cin >> x;
    vector<int> fa(4*n),sz1(4*n),sz2(4*n);
    iota(fa.begin(),fa.end(),0);
    function<int(int)> fp=[&](int u){
        return fa[u]=u==fa[u]?u:fp(fa[u]);
    };
    auto merge=[&](int u,int v){
        u=fp(u),v=fp(v);
        if(u==v)return;
        fa[v]=u;
        sz1[u]+=sz1[v];
        sz2[u]+=sz2[v];
    };
    for(int i=0;i<2*n;i++){
        sz1[i]=1;
        sz2[i+2*n]=1;
    }
    vector<int> st;
    for(int i=0;i<2*n;i++){
        int id=-1;
        while(!st.empty()&&a[st.back()]>a[i]){
            int j=st.back();
            st.pop_back();
            if(id==-1){
                id=j;
            }else{
                merge(id,j);
                merge(id+2*n,j+2*n);
            }
        }
        st.emplace_back(i);
        if(id!=-1){
            merge(id,i+2*n);
            merge(id+2*n,i);
            st.emplace_back(id);
        }
    }
    for(int i=0;i<2*n;i++){
        if(fp(i)==fp(i+2*n)){
            cout << "No\n";
            return;
        }
    }
    int base=0;
    vector<int> cnt(n+1);
    for(int i=0;i<2*n;i++){
        if(i==fp(i)){
            int x=sz1[i],y=sz2[i];
            if(x<y)swap(x,y);
            base+=y;
            if(x-y>n){
                cout << "No\n";
                return;
            }
            cnt[x-y]++;
        }
    }
    if(base>n){
        cout << "No\n";
        return;
    }
    bitset<N> dp;
    dp[0]=1;
    for(int i=1;i<=n;i++){
        while(cnt[i]>2){
            cnt[i]-=2;
            cnt[i*2]++;
        }
        while(cnt[i]--){
            dp|=dp<<i;
        }
    }
    cout << (dp[n-base]?"Yes":"No") << "\n";
}

void runcase(){
    int n;
    cin >> n;
    solve<1>(n);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}