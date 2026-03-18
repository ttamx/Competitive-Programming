#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct Fenwick{
    int n;
    vector<int> t;
    Fenwick(int _n):n(_n),t(_n+1){}
    void update(int i,int v){
        for(;i<=n;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
};

vector<int> z_algo(const string &s){
    int n=s.size();
    vector<int> z(n);
    z[0]=n;
    for(int i=1,l=0,r=0;i<n;i++){
        if(i<r)z[i]=min(z[i-l],r-i);
        while(i+z[i]<n&&s[z[i]]==s[i+z[i]])z[i]++;
        if(i+z[i]>r)l=i,r=i+z[i];
    }
    return z;
}

void solve(){
    int n;
    cin >> n;
    string a,b;
    cin >> a >> b;
    string s=a+a+b+b;
    auto za=z_algo(s);
    reverse(s.begin(),s.end());
    auto zb=z_algo(s);
    reverse(zb.begin(),zb.end());   
    vector<vector<int>> event(n);
    for(int i=0;i<n;i++){
        if(za[i+n]>0){
            event[min(za[i+n],n)-1].emplace_back(n-i);
        }
    }
    ll ans=0;
    Fenwick f(n);
    for(int i=0;i<n;i++){
        int x=min(zb[i+2*n],n);
        if(x>0)f.update(x,+1);
        for(auto v:event[i]){
            ans+=f.query(n)-f.query(v-1);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}