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
    int x1,y1,x2,y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int n;
    cin >> n;
    map<pair<int,int>,bool> ok;
    map<pair<int,int>,int> dist;
    for(int i=0;i<n;i++){
        int x,l,r;
        cin >> x >> l >> r;
        for(int j=l;j<=r;j++){
            ok[{x,j}]=true;
        }
    }
    queue<pair<int,int>> q;
    q.emplace(x1,y1);
    dist[{x1,y1}]=0;
    while(!q.empty()){
        auto [i,j]=q.front();
        q.pop();
        int d=dist[{i,j}];
        if(i==x2&&j==y2)return void(cout << d << "\n");
        for(auto dx:{-1,0,1}){
            for(auto dy:{-1,0,1}){
                int x=i+dx,y=j+dy;
                if(ok.count({x,y})&&!dist.count({x,y})){
                    dist[{x,y}]=d+1;
                    q.emplace(x,y);
                }
            }
        }
    }
    cout << -1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}