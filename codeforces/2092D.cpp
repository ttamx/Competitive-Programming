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
    string s;
    cin >> s;
    int cl=0,ci=0,ct=0;
    for(auto x:s){
        if(x=='L')cl++;
        else if(x=='I')ci++;
        else ct++;
    }
    if(cl==n||ci==n||ct==n){
        cout << -1 << "\n";
        return;
    }
    vector<int> ans;
    auto work=[&](int i){
        assert(s[i]!=s[i+1]);
        ans.emplace_back(i);
        char c=s[i]^s[i+1]^'L'^'I'^'T';
        s.insert(s.begin()+i+1,c);
    };
    if(cl>0){
        int id=-1;
        for(int i=0;i+1<s.size();i++){
            if(s[i]!=s[i+1]&&(s[i]=='L'||s[i+1]=='L')){
                id=i;
                break;
            }
        }
        assert(id!=-1);
        if(s[id]=='L'){
            for(int i=0;i<cl*2;i++){
                work(id);
            }
        }else{
            for(int i=0;i<cl*2;i++){
                work(id+i);
            }
        }
    }
    if(ci>0){
        int id=-1;
        for(int i=0;i+1<s.size();i++){
            if(s[i]!=s[i+1]&&(s[i]=='I'||s[i+1]=='I')){
                id=i;
                break;
            }
        }
        assert(id!=-1);
        if(s[id]=='I'){
            for(int i=0;i<ci*2;i++){
                work(id);
            }
        }else{
            for(int i=0;i<ci*2;i++){
                work(id+i);
            }
        }
    }
    if(ct>0){
        int id=-1;
        for(int i=0;i+1<s.size();i++){
            if(s[i]!=s[i+1]&&(s[i]=='T'||s[i+1]=='T')){
                id=i;
                break;
            }
        }
        assert(id!=-1);
        if(s[id]=='T'){
            for(int i=0;i<ct*2;i++){
                work(id);
            }
        }else{
            for(int i=0;i<ct*2;i++){
                work(id+i);
            }
        }
    }
    cout << ans.size() << "\n";
    for(auto x:ans){
        cout << x+1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}