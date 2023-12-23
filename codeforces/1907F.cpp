#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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
const int MOD=1000000007;
// const int MOD=998224353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

void runcase(){
    int n;
    cin >> n;
    vi a(n);
    for(auto &x:a)cin >> x;
    if(*max_element(all(a))==*min_element(all(a)))return void(cout << "0\n");
    int mn=*min_element(all(a));
    int l,r;
    for(int i=0;i<n;i++){
        if(a[i]==mn){
            l=r=i;
            while(r+1<n&&a[r+1]==mn)r++;
            break;
        }
    }
    if(l==0&&a[n-1]==mn){
        l=n-1;
        while(a[l-1]==mn)l--;
    }
    auto solve1=[&](){
        for(int i=0;i<n-1;i++)if(a[(l+i+1)%n]<a[(l+i)%n])return INF;
        if(l==0)return 0;
        return min(n-l,l+2);
    };
    auto solve2=[&](){
        for(int i=0;i<n-1;i++)if(a[(r+n-i-1)%n]<a[(r+n-i)%n])return INF;
        if(r==n-1)return 1;
        return min(n-r-1,r+1)+1;
    };
    int ans=min(solve1(),solve2());
    cout << (ans<=2*n?ans:-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}