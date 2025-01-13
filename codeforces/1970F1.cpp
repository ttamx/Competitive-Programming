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
    int bi,bj;
    vector<vector<bool>> bg(n,vector<bool>(m));
    vector<vector<bool>> rg(n,vector<bool>(m));
    map<string,pair<int,int>> pos;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            string s;
            cin >> s;
            if(s==".Q"){
                bi=i,bj=j;
            }else if(s=="BG"){
                bg[i][j]=true;
            }else if(s=="RG"){
                rg[i][j]=true;
            }else if(s!=".."){
                pos[s]={i,j};
            }
        }
    }
    int bs=0,rs=0;
    int q;
    cin >> q;
    for(int t=0;t<q;t++){
        string name;
        char op;
        cin >> name >> op;
        auto &[i,j]=pos[name];
        if(op=='T'){
            if(rg[i][j]){
                cout << t << " BLUE GOAL\n";
                bs++;
                bi=n/2,bj=m/2;
            }else if(bg[i][j]){
                cout << t << " RED GOAL\n";
                rs++;
                bi=n/2,bj=m/2;
            }else{
                bi=i,bj=j;
            }
        }else if(op=='C'){
            string ball;
            cin >> ball;
        }else if(op=='U'){
            i--;
        }else if(op=='D'){
            i++;
        }else if(op=='L'){
            j--;
        }else if(op=='R'){
            j++;
        }
    }
    cout << "FINAL SCORE: " << rs << " " << bs << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}