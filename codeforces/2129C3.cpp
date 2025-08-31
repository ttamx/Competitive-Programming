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

vector<int> len,val;

void runcase(){
    int n;
    cin >> n;
    auto ask=[&](vector<int> a){
        cout << "? " << a.size();
        for(auto x:a){
            cout << " " << x+1;
        }
        cout << endl;
        int res;
        cin >> res;
        return res;
    };
    int s=-1;
    {
        vector<int> cands(n);
        iota(cands.begin(),cands.end(),0);
        if(ask(cands)==0){
            reverse(cands.begin(),cands.end());
        }
        int l=0,r=n-2;
        while(l<r){
            int m=(l+r+1)/2;
            if(ask(vector<int>(cands.begin()+m,cands.end()))>0)l=m;
            else r=m-1;
        }
        s=cands[l];
    }
    string ans(n,'(');
    int cnt=0;
    vector<int> a,id;
    auto solve=[&](){
        int res=ask(a);
        for(int i=cnt-1;i>=0;i--){
            if(res>=val[i]){
                res-=val[i];
                ans[id[i]]=')';
            }
        }
        assert(res==0);
        a.clear();
        id.clear();
        cnt=0;
    };
    for(int i=0;i<n;i++){
        if(i==s)continue;
        a.emplace_back(s);
        for(int t=0;t<len[cnt];t++){
            a.emplace_back(s);
            a.emplace_back(i);
        }
        id.emplace_back(i);
        cnt++;
        if(cnt==len.size()){
            solve();
        }
    }
    if(cnt>0){
        solve();
    }
    cout << "! " << ans << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int sum=0;
    int cnt=0;
    int cur=0,num=0;
    while(true){
        while(cur<=sum){
            num++;
            cur+=num;
        }
        if(cnt+2*num+1>1000)break;
        cnt+=2*num+1;
        sum+=cur;
        len.emplace_back(num);
        val.emplace_back(cur);
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}