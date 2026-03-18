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
    int n,q;
    cin >> n >> q;
    string s;
    cin >> s;
    int base=0;
    int tot=count(s.begin(),s.end(),'?');
    int a=0,b=0,c=0,d=0;
    for(int i=0;i<n;i++){
        if(s[i]=='X'){
            base+=10;
        }else if(s[i]=='V'){
            base+=5;
        }else if(s[i]=='I'){
            if(i+1<n&&(s[i+1]=='X'||s[i+1]=='V')){
                base--;
            }else{
                base++;
            }
        }else if(s[i]=='?'){
            int j=i;
            while(j+1<n&&s[j+1]=='?'){
                j++;
            }
            int sz=j-i+1;
            bool l=(i>0)&&(s[i-1]=='I');
            bool r=(j+1<n)&&(s[j+1]=='X'||s[j+1]=='V');
            if(l&&r){
                if(sz==1){
                    d++;
                }else{
                    a+=sz/2-1;
                    b++;
                    c++;
                }
            }else if(l){
                a+=(sz-1)/2;
                b++;
            }else if(r){
                a+=(sz-1)/2;
                c++;
            }else{
                a+=sz/2;
            }
            i=j;
        }
    }
    while(q--){
        int x,y,z;
        cin >> z >> y >> x;
        x=min(x,tot);
        y=min(y,tot-x);
        z=min(z,tot-x-y);
        assert(x+y+z==tot);
        int ans=base+x+y*5+z*10;
        y+=z;
        ans-=min(y,b)*2;
        y-=min(y,b);
        ans-=min(x,c)*2;
        x-=min(x,c);
        int e=d;
        if(x>y){
            int used=min(x-y,e);
            ans-=used*2;
            e-=used;
            x-=used;
        }else{
            int used=min(y-x,e);
            ans-=used*2;
            e-=used;
            y-=used;
        }
        ans-=min(x,e/2)*2;
        ans-=min(y,e-e/2)*2;
        ans-=min({x,y,a})*2;
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}