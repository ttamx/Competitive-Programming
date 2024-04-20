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
const int MOD=1000000007;
// const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

bool cmp(string a,string b){
    reverse(all(a));
    reverse(all(b));
    while(sz(a)<sz(b))a.push_back('0');
    while(sz(a)>sz(b))b.push_back('0');
    reverse(all(a));
    reverse(all(b));
    return a<b;
};

void chmin(string &s,const string &t){
    if(cmp(t,s))s=t;
}

string rev(string s){
    reverse(all(s));
    while(s.back()=='1')s.pop_back();
    return s;
}

string work1(string s,int k){
    int l=0,r=sz(s)-1;
    for(int i=0;i<k;i++){
        while(l<r&&s[l]=='0')l++;
        while(l<r&&s[r]=='1')r--;
        if(l<r)swap(s[l],s[r]);
    }
    return s;
}

string work2(string s,int k){
    int cnt=0;
    while(!s.empty()&&k>0){
        if(s.back()=='1'){
            k--;
            cnt++;
        }
        s.pop_back();
    }
    while(!s.empty()&&s.back()=='0')s.pop_back();
    if(k>0)return string(cnt,'1');
    for(auto &x:s){
        if(x=='0'){
            x='1';
            cnt--;
        }
        if(cnt==0)break;
    }
    while(cnt--)s.push_back('1');
    reverse(all(s));
    return s;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    string s;
    cin >> s;
    auto ans=work1(s,k);
    chmin(ans,work2(s,k-1));
    reverse(all(ans));
    ll res=0;
    while(ans.back()=='0')ans.pop_back();
    reverse(all(ans));
    for(auto x:ans)res=(res*2+x-'0')%MOD;
    cout << res;
}