#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;

vi prefix_function(const string &s){
    int n=sz(s);
    vi pi(n);
    for(int i=1,j=0;i<n;i++){
        while(j&&s[i]!=s[j])j=pi[j-1];
        if(s[i]==s[j])j++;
        pi[i]=j;
    }
    return pi;
}

vi z_function(const string &s){
    int n=sz(s);
    vi z(n);
    for(int i=1,l=0,r=0;i<n;i++){
        if(i>r){
            l=r=i;
            while(r<n&&s[r-l]==s[r])r++;
            z[i]=r-l,r--;
        }else{
            int k=i-l;
            if(s[k]<r-i+1)z[i]=z[k];
            else{
                l=i;
                while(r<n&&s[r-l]==s[r])r++;
                z[i]=r-l,r--;
            }
        }
    }
    return z;
}

const int N=1e5+5;

int n,m;
string s,t;
ll cnt[N];
ll ans;

void brute(){
    set<string> st;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)st.emplace(s.substr(0,i)+t.substr(0,j));
    cout << st.size() << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> s >> t;
    n=sz(s),m=sz(t);
    brute();
    ans=n*m;
    string ts=t+"$"+s;
    vi p=prefix_function(t),l=z_function(ts);
    for(auto x:p)cerr << x << " ";
    cerr << "\n";
    for(auto x:l)cerr << x << " ";
    cerr << "\n";
    for(int i=1;i<m;i++)cnt[i+1-p[i]]++;
    for(int i=1;i<=max(n,m);i++)cnt[i]+=cnt[i-1];
    for(int i=1;i<n;i++)ans-=cnt[l[i+m]];
    cout << ans << "\n";
}