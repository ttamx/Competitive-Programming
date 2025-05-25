#include<bits/stdc++.h>

using namespace std;

const int MOD=998244353;

using ll = long long;
using P = pair<int,int>;

struct Matrix:array<array<ll,2>,2>{
    Matrix(){
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                this->at(i).at(j)=0;
            }
        }
    }
    static Matrix identity(){
        Matrix res;
        res[0][0]=res[1][1]=1;
        return res;
    }
    friend Matrix operator*(const Matrix &l,const Matrix &r){
        Matrix res;
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                for(int k=0;k<2;k++){
                    res[i][j]+=l[i][k]*r[k][j];
                }
            }
        }
        return res;
    }
};

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<P> e(m);
    for(auto &[l,r]:e){
        cin >> l >> r;
    }
    Matrix base;
    base[0][0]=1;
    base[1][0]=k;
    base[1][1]=k-1;
    vector<Matrix> dp(30);
    dp[0]=base;
    for(int i=1;i<30;i++){
        dp[i]=dp[i-1]*dp[i-1];
    }
    auto calc=[&](int len)->ll {
        if(len==1)return 1;
        if(len==1)return k;
        ll w=1LL*k*(k-1)%MOD;
        if(len==2)return w;
        len-=2;
        Matrix res=Matrix::identity();
        for(int i=0;i<30;i++){
            if(len>>i&1){
                res=res*base;
            }
        }
        return (w*res[0][0]+res[1][0])%MOD;
    };
    for(int i=0;i<m;i++){
        e.emplace_back(e[i].first,e[i].first);
    }
    e.emplace_back(1,n);
    sort(e.begin(),e.end(),[&](const P &x,const P &y){
        return x.second<y.second||(x.second==y.second&&x.first>y.first);
    });
    ll ans=1;
    int last=1;
    stack<pair<int,int>> s;
    for(auto [l,r]:e){
        cerr << "(" << l << " " << r << ") : ";
        if(r>last){
            s.emplace(last,r-last);
            last=r;
        }
        if(l==r)continue;
        int cur=1;
        int pre=r;
        while(!s.empty()&&s.top().first>=l){
            auto [pos,sz]=s.top();
            s.pop();
            cur+=sz;
            pre=pos;
        }
        s.emplace(pre,1);
        cerr << cur << "\n";
        ans=ans*calc(cur)%MOD;
    }
    cerr << "\n";
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        runcase();
    }
}