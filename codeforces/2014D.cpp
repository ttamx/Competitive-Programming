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
    int n,d,k;
    cin >> n >> d >> k;
    vector<pair<int,int>> a;
    vector<int> add(n+1),del(n+1);
    for(int i=0;i<k;i++){
        int l,r;
        cin >> l >> r;
        add[l]++;
        del[r]++;
    }
    deque<int> dq;
    int ans1=0,ans2=0,mx=-1,mn=n+1,cur=0;
    for(int i=1;i<=n;i++){
        cur+=add[i];
        while(!dq.empty()&&i-dq.front()+1>d){
            dq.pop_front();
        }
        if(i>=d){
            int res=cur+dq.size();
            if(res>mx){
                mx=res;
                ans1=i-d+1;
            }
            if(res<mn){
                mn=res;
                ans2=i-d+1;
            }
        }
        for(int j=0;j<del[i];j++){
            dq.emplace_back(i);
            cur--;
        }
    }
    cout << ans1 << " " << ans2 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}