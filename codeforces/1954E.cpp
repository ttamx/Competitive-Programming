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

const int N=1e5+5;

int n;
int a[N],b[N];
int mx;
vector<int> id[N];
ll ans=0;

void upd(int i,int v){
    if(i>0)ans-=max(b[i]-b[i-1],0);
    if(i+1<n)ans-=max(b[i+1]-b[i],0);
    b[i]=v;
    if(i>0)ans+=max(b[i]-b[i-1],0);
    if(i+1<n)ans+=max(b[i+1]-b[i],0);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++)cin >> a[i];
    mx=*max_element(a,a+n);
    for(int i=0;i<n;i++){
        for(int j=1;j*j<=a[i];j++)id[j+1].emplace_back(i);
        for(int j=1;j*j<=a[i];j++)id[(a[i]-1)/j+1].emplace_back(i);
    }
    for(int i=0;i<n;i++)b[i]=a[i];
    for(int i=1;i<n;i++)ans+=max(b[i]-b[i-1],0);
    for(int i=1;i<=mx;i++){
        for(auto j:id[i])upd(j,(a[j]+i-1)/i);
        cout << b[0]+ans << " \n"[i==mx];
    }
}