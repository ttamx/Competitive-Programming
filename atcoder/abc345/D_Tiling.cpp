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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,h,w;
    cin >> n >> h >> w;
    vi a(n),b(n);
    for(int i=0;i<n;i++)cin >> a[i] >> b[i];
    for(int mask=0;mask<1<<n;mask++){
        vi id(n);
        iota(all(id),0);
        do{
            int i=0,j=0;
            vector<vi> cnt(h,vi(w));
            for(auto idx:id){
                while(i<h&&cnt[i][j])if(++j==w)i++,j=0;
                if(i==h)cout << "Yes",exit(0);
                int x=a[idx],y=b[idx];
                if(mask>>idx&1)swap(x,y);
                if(i+x>h||j+y>w)continue;
                bool ok=true;
                for(int xx=0;xx<x;xx++){
                    for(int yy=0;yy<y;yy++){
                        if(cnt[i+xx][j+yy]){
                            ok=false;
                            break;
                        }
                    }
                    if(!ok)break;
                }
                if(!ok)continue;
                for(int xx=0;xx<x;xx++){
                    for(int yy=0;yy<y;yy++){
                        cnt[i+xx][j+yy]++;
                    }
                }
            }
            while(i<h&&cnt[i][j])if(++j==w)i++,j=0;
            if(i==h)cout << "Yes",exit(0);
        }while(next_permutation(all(id)));
    }
    cout << "No";
}