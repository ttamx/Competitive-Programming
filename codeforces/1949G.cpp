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
    int n;
    cin >> n;
    string s,e;
    cin >> e >> s;
    vector<int> sm,sc,em,ec,mc,cm;
    int inic=0,inim=0,reqc=0,reqm=0;
    for(int i=0;i<n;i++){
        if(s[i]==e[i])continue;
        if(s[i]=='C')inic++;
        if(s[i]=='M')inim++;
        if(e[i]=='C')reqc++;
        if(e[i]=='M')reqm++;
        if(s[i]=='-'){
            (e[i]=='C'?ec:em).emplace_back(i);
        }else if(e[i]=='-'){
            (s[i]=='C'?sc:sm).emplace_back(i);
        }else{
            (s[i]=='M'?mc:cm).emplace_back(i);
        }
    }
    while(inic>reqc&&!cm.empty()){
        em.emplace_back(cm.back());
        cm.pop_back();
        inic--;
    }
    while(inim>reqm&&!mc.empty()){
        ec.emplace_back(mc.back());
        mc.pop_back();
        inim--;
    }
    while(inic>reqc){
        assert(!sc.empty());
        sc.pop_back();
        inic--;
    }
    while(inim>reqm){
        assert(!sm.empty());
        sm.pop_back();
        inim--;
    }
    vector<int> ans;
    for(int t=0;t<2;t++){
        for(auto x:sc){
            ans.emplace_back(x);
            ans.emplace_back(-1);
            int cur=0;
            while(true){
                if(cur==0&&!mc.empty()){
                    ans.emplace_back(mc.back());
                    mc.pop_back();
                    ans.emplace_back(-2);
                    ans.emplace_back(-1);
                    cur^=1;
                }else if(cur==1&&!cm.empty()){
                    ans.emplace_back(cm.back());
                    cm.pop_back();
                    ans.emplace_back(-2);
                    ans.emplace_back(-1);
                    cur^=1;
                }else{
                    break;
                }
            }
            if(cur==0){
                assert(!ec.empty());
                ans.emplace_back(ec.back());
                ec.pop_back();
                ans.emplace_back(-2);
            }else{
                assert(!em.empty());
                ans.emplace_back(em.back());
                em.pop_back();
                ans.emplace_back(-2);
            }
        }
        swap(sc,sm);
        swap(ec,em);
        swap(cm,mc);
    }
    cout << ans.size() << "\n";
    for(auto x:ans){
        if(x==-1){
            cout << "PICKUP\n";
        }else if(x==-2){
            cout << "DROPOFF\n";
        }else{
            cout << "DRIVE " << x+1 << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}