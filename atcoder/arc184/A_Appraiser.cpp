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

void runcase(){
    int n,m,q;
    cin >> n >> m >> q;
    int cnt=0;
    auto ask=[&](int x,int y){
        ++cnt;
        if(cnt>q)while(true);
        cout << "? " << x+1 << " " << y+1 << endl;
        int res;
        cin >> res;
        return res;
    };
    vector<int> ans,cur,ans2;
    int bad=-1;
    for(int i=0;i<n;i++){
        if(cur.empty()){
            cur.emplace_back(i);
            continue;
        }
        int res=ask(cur[0],i);
        if(res==0){
            cur.emplace_back(i);
            if(min(ans.size(),ans2.size())+cur.size()>m){
                bad=i;
                cur.clear();
            }
        }else{
            if(ans.empty()||ask(ans[0],i)==0){
                ans.emplace_back(i);
                ans2.insert(ans2.end(),cur.begin(),cur.end());
            }else{
                ans.insert(ans.end(),cur.begin(),cur.end());
                ans2.emplace_back(i);
            }
            cur.clear();
        }
    }
    if(!cur.empty()){
        if(ans.empty()||ask(ans[0],cur[0])==0){
            ans.insert(ans.end(),cur.begin(),cur.end());
        }else{
            ans2.insert(ans2.end(),cur.begin(),cur.end());
        }
    }
    if(bad!=-1){
        if(ask(ans[0],bad)==0){
            swap(ans,ans2);
        }
    }else if(ans.size()!=m){
        swap(ans,ans2);
    }
    if(ans.size()!=m){
        while(true);
    }
    cout << "!";
    for(auto x:ans){
        cout << " " << x+1;
    }
    cout << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}