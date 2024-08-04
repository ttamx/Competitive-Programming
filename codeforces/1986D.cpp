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
    string s;
    cin >> n >> s;
    if(n==2)return void(cout << stoi(s) << "\n");
    if(s[0]=='0'||s.back()=='0')return void(cout << "0\n");
    if(n==3&&s[1]=='0'){
        int ans=INF;
        ans=min(ans,(s[0]-'0')*stoi(s.substr(1,2)));
        ans=min(ans,(s[0]-'0')+stoi(s.substr(1,2)));
        ans=min(ans,stoi(s.substr(0,2))*(s[2]-'0'));
        ans=min(ans,stoi(s.substr(0,2))+(s[2]-'0'));
        cout << ans << "\n";
        return;
    }
    for(auto x:s)if(x=='0')return void(cout << "0\n");
    int ans=INF;
    for(int i=0;i+1<n;i++){
        int sum=0;
        for(int j=i-1;j>=0;j--)if(s[j]!='1')sum+=s[j]-'0';
        for(int j=i+2;j<n;j++)if(s[j]!='1')sum+=s[j]-'0';
        ans=min(ans,sum+stoi(s.substr(i,2)));
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}