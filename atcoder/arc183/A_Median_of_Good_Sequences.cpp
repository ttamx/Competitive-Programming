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
    int n,k;
    cin >> n >> k;
    if(n==1){
        for(int i=0;i<k;i++){
            cout << 1 << " ";
        }
        cout << "\n";
        return;
    }
    vector<int> ans;
    if(n%2==0){
        int x=n/2;
        ans.emplace_back(x);
        for(int i=n;i>=1;i--){
            int cnt=k;
            if(i==x)cnt--;
            for(int j=0;j<cnt;j++){
                ans.emplace_back(i);
            }
        }
    }else{
        int x=(n+1)/2;
        for(int i=0;i<k;i++)ans.emplace_back(x);
        vector<int> num;
        for(int i=1;i<=n;i++){
            if(i!=x){
                num.emplace_back(i);
            }
        }
        int y=num[(n-1)/2-1];
        ans.emplace_back(y);
        reverse(num.begin(),num.end());
        for(int i:num){
            int cnt=k;
            if(i==y)cnt--;
            for(int j=0;j<cnt;j++){
                ans.emplace_back(i);
            }
        }
    }
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}