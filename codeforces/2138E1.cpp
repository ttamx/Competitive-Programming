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

const int S=80;

void runcase(){
    int x;
    // x=rng()%int(1e7);
    // cerr << x << " ";
    cin >> x;
    vector<vector<int>> ans(S,vector<int>(S));
    vector<int> naf;
    for(int n=x;n>0;n/=2){
        if(n%2==1){
            int v=2-n%4;
            naf.emplace_back(v);
            n-=v;
        }else{
            naf.emplace_back(0);
        }
    }
    while(naf.size()<2)naf.emplace_back(0);
    int b=naf.size()*2;
    int cnt=0;
    int cur=b-1;
    for(int i=0;i<b-1;i++){
        if(i%2==0){
            ans[i][i]=1;
            if(i+1<b-1)ans[i][i+1]=-1;
            if(naf[i/2]){
                if(++cnt==3){
                    cnt=2;
                    ans[cur][cur]=1;
                    ans[cur][cur+1]=-1;
                    cur++;
                }
                ans[i][cur]=-naf[i/2];
            }
        }else{
            ans[i][i]=1;
            if(i+1<b-1)ans[i][i+1]=-1;
            if(i+2<b-1)ans[i][i+2]=-1;
        }
    }
    for(int i=0;i<=cur;i++){
        int tmp=0;
        for(int j=0;j<=cur;j++){
            if(ans[i][j]){
                // cerr << j << " ";
                tmp++;
            }
        }
        // cerr << "\n";
        // cerr << "ROW " << i << " " << tmp << "\n";
        assert(tmp<=3);
    }
    for(int i=0;i<=cur;i++){
        int tmp=0;
        for(int j=0;j<=cur;j++){
            if(ans[j][i]){
                // cerr << j << " ";
                tmp++;
            }
        }
        // cerr << "\n";
        // cerr << "COL " << i << " " << tmp << "\n";
        assert(tmp<=3);
    }
    ans[cur][0]=1;
    ans[cur][1]=1;
    cout << cur+1 << "\n";
    for(int i=0;i<=cur;i++){
        for(int j=0;j<=cur;j++){
            cout << ans[i][j] << " \n"[j==cur];
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}