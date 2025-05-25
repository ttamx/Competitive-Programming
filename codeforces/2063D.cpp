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

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n),b(m);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    int k=min({n,m,(n+m)/3});
    vector<int> v1,v2;
    for(int l=0,r=n-1;l<r;l++,r--){
        v1.emplace_back(a[r]-a[l]);
    }
    for(int l=0,r=m-1;l<r;l++,r--){
        v2.emplace_back(b[r]-b[l]);
    }
    ll base=0;
    vector<ll> ans(k);
    int pos1=0,pos2=0;
    int cnt1=n,cnt2=m;
    int cur=0;
    while(cur<k&&(pos1<v1.size()||pos2<v2.size())){
        ll val1=(cnt1>=2&&cnt2>=1&&pos1<v1.size())?v1[pos1]:-1;
        ll val2=(cnt2>=2&&cnt1>=1&&pos2<v2.size())?v2[pos2]:-1;
        if(val1<0&&val2<0){
            if(cnt2==0){
                swap(v1,v2);
                swap(pos1,pos2);
                swap(cnt1,cnt2);
            }
            for(int i=pos1-1;i>=0;i--){
                base-=v1[i];
                cnt1+=2,cnt2+=1;
                cur--;
                while(pos2<v2.size()&&cnt2>=2&&cnt1>=1){
                    base+=v2[pos2];
                    cnt2-=2,cnt1-=1;
                    ans[cur]=max(ans[cur],base);
                    cur++;
                    pos2++;
                }
            }
            break;
        }else if(val1>val2){
            base+=v1[pos1];
            cnt1-=2,cnt2-=1;
            ans[cur]=max(ans[cur],base);
            cur++;
            pos1++;
        }else{
            base+=v2[pos2];
            cnt2-=2,cnt1-=1;
            ans[cur]=max(ans[cur],base);
            cur++;
            pos2++;
        }
    }
    cout << k << "\n";
    for(int i=0;i<k;i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}