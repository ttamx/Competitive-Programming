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
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

vi prefix_function(const string &s){
    int n=sz(s);
    vi pi(n);
    for(int i=1,j=0;i<n;i++){
        for(j=pi[i-1];j>0&&s[i]!=s[j];j=pi[j-1]);
        if(s[i]==s[j])j++;
        pi[i]=j;
    }
    return pi;
}

void runcase(string s){
    int n=sz(s);
    vi pi=prefix_function(s);
    int k=n-pi[n-1];
    cout << (n%k==0?n/k:1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    while((cin >> s)&&s!="*")runcase(s);
}