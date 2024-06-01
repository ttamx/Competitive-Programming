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
    map<int,int> cnt;
    int sum=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt[x]++;
        sum^=x;
    }
    if(n==1)return void(cout << cnt.begin()->first << "\n");
    if(!sum||sz(cnt)<2)return void(cout << "-1\n");
    int st=-1;
    for(auto [x,y]:cnt)if(y%2&&(st==-1||y<cnt[st]))st=x;
    int cur=cnt[st]-1;
    cnt[st]=0;
    vi b{st};
    deque<int> dq;
    for(auto &[x,y]:cnt){
        while(y>1){
            b.emplace_back(x);
            while(cur>0){
                b.emplace_back(st);
                cur--;
            }
            b.emplace_back(x);
            y-=2;
        }
        if(y)dq.emplace_back(x);
    }
    if(!dq.empty()){
        int val=dq.front()^st;
        b.emplace_back(dq.front());
        dq.pop_front();
        while(cur>0){
            b.emplace_back(st);
            cur--;
        }
        while(!dq.empty()){
            if(val==dq.front()){
                val^=dq.back();
                b.emplace_back(dq.back());
                dq.pop_back();
            }else{
                val^=dq.front();
                b.emplace_back(dq.front());
                dq.pop_front();
            }
        }
    }
    for(auto x:b)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}