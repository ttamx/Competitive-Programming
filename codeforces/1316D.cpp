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
    vector a(n,vector<pair<int,int>>(n));
    for(auto &v:a)for(auto &[x,y]:v){
        cin >> x >> y;
        if(x!=-1)x--,y--;
    }
    vector ans(n,string(n,'.'));
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(a[i][j]==make_pair(i,j)){
        pair<int,int> st(i,j);
        auto valid=[&](int i,int j){
            return 0<=i&&i<n&&0<=j&&j<n&&a[i][j]==st&&ans[i][j]=='.';
        };
        queue<pair<int,int>> q;
        q.emplace(i,j);
        ans[i][j]='X';
        while(!q.empty()){
            auto [i,j]=q.front();
            q.pop();
            if(valid(i,j-1)){
                ans[i][j-1]='R';
                q.emplace(i,j-1);
            }
            if(valid(i,j+1)){
                ans[i][j+1]='L';
                q.emplace(i,j+1);
            }
            if(valid(i-1,j)){
                ans[i-1][j]='D';
                q.emplace(i-1,j);
            }
            if(valid(i+1,j)){
                ans[i+1][j]='U';
                q.emplace(i+1,j);
            }
        }
    }
    auto check=[&](int i,int j){
        return 0<=i&&i<n&&0<=j&&j<n&&a[i][j]==make_pair(-1,-1)&&ans[i][j]!='.';
    };
    auto check2=[&](int i,int j){
        return 0<=i&&i<n&&0<=j&&j<n&&a[i][j]==make_pair(-1,-1)&&ans[i][j]=='.';
    };
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(a[i][j]==make_pair(-1,-1)){
        if(ans[i][j]!='.')continue;
        if(check(i,j-1))ans[i][j]='L';
        else if(check(i,j+1))ans[i][j]='R';
        else if(check(i-1,j))ans[i][j]='U';
        else if(check(i+1,j))ans[i][j]='D';
        else if(check2(i,j-1))ans[i][j]='L',ans[i][j-1]='R';
        else if(check2(i,j+1))ans[i][j]='R',ans[i][j+1]='L';
        else if(check2(i-1,j))ans[i][j]='U',ans[i-1][j]='D';
        else if(check2(i+1,j))ans[i][j]='D',ans[i+1][j]='U';
        else return void(cout << "INVALID\n");
    }
    for(auto &s:ans)for(auto &x:s)if(x=='.')return void(cout << "INVALID\n");
    cout << "VALID\n";
    for(auto &s:ans)cout << s << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}