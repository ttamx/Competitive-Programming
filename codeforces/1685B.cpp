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
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    string s;
    cin >> s;
    int n=s.size();
    int ca=0,cb=0,sum=0;
    vector<int> ab,ba;
    for(auto x:s){
        if(x=='A'){
            ca++;
        }else{
            cb++;
        }
    }
    if(ca!=a+c+d||cb!=b+c+d){
        cout << "NO\n";
        return;
    }
    for(int i=0;i<n;i++){
        int j=i;
        while(j+1<n&&s[j]!=s[j+1])j++;
        if(i!=j){
            int len=j-i+1;
            if(len%2==1){
                sum+=len/2;
            }else if(s[i]=='A'){
                ab.emplace_back(len/2);
            }else{
                ba.emplace_back(len/2);
            }
        }
        i=j;
    }
    sort(ab.begin(),ab.end());
    sort(ba.begin(),ba.end());
    for(auto x:ab){
        if(x<=c){
            c-=x;
        }else{
            sum+=x-1;
        }
    }
    for(auto x:ba){
        if(x<=d){
            d-=x;
        }else{
            sum+=x-1;
        }
    }
    cout << (c+d<=sum?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}