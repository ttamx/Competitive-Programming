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
    int n;
    cin >> n;
    deque<char> dq;
    for(int i=0;i<n;i++){
        char c;
        cin >> c;
        dq.emplace_back(c);
    }
    auto work=[&](int k){
        while(sz(dq)>=2*k){
            bool ok=true;
            for(int i=0;i<k;i++)if(dq[i]!=dq[2*k-i-1]){
                ok=false;
                break;
            }
            if(!ok)break;
            for(int i=0;i<k;i++)dq.pop_front();
        }
        while(sz(dq)>=2*k){
            bool ok=true;
            for(int i=0;i<k;i++)if(dq.end()[-k+i]!=dq.end()[-k-i-1]){
                ok=false;
                break;
            }
            if(!ok)break;
            for(int i=0;i<k;i++)dq.pop_back();
        }
        deque<char> ndq;
        for(auto x:dq){
            ndq.emplace_back(x);
            if(sz(ndq)>=3*k){
                bool ok=true;
                for(int i=0;i<k;i++)if(ndq.end()[-k+i]!=ndq.end()[-k-i-1]){
                    ok=false;
                    break;
                }
                if(!ok)continue;
                for(int i=0;i<k;i++)if(ndq.end()[-3*k+i]!=ndq.end()[-k-i-1]){
                    ok=false;
                    break;
                }
                if(!ok)continue;
                for(int i=0;i<2*k;i++)ndq.pop_back();
            }
        }
        swap(dq,ndq);
    };
    for(int i=1;i<30;i++)work(i);
    cout << sz(dq) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}