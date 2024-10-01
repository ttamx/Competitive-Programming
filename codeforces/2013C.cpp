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
    deque<char> s;
    auto ask=[&](){
        cout << "? ";
        for(auto x:s)cout << x;
        cout << endl;
        int res;
        cin >> res;
        return res;
    };
    s.emplace_back('0');
    if(!ask()){
        cout << "! " << string(n,'1') << endl;
        return;
    }
    int cur=0;
    while(s.size()<n){
        while(s.size()<n){
            s.emplace_back('0'+cur);
            if(!ask()){
                s.pop_back();
                break;
            }
        }
        cur^=1;
        if(s.size()<n){
            s.emplace_back('0'+cur);
            if(!ask()){
                s.pop_back();
                break;
            }
        }
    }
    cur=1;
    while(s.size()<n){
        while(s.size()<n){
            s.emplace_front('0'+cur);
            if(!ask()){
                s.pop_front();
                break;
            }
        }
        cur^=1;
    }
    cout << "! ";
    for(auto x:s){
        cout << x;
    }
    cout << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}