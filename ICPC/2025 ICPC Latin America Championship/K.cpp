#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll L=1e9;
const int B=31;

struct Info{
    ll mul,add,mul2,add2;
    friend Info operator+(const Info &l,const Info &r){
        return Info{
                min(l.mul*r.mul,L),
                min(l.add*r.mul+r.add,L),
                min(l.mul2+l.mul*r.mul2,L),
                min(l.add2+l.add*r.mul2+r.add2,L)
        };
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll n,p,h;
    cin >> n >> p >> h;
    vector<ll> add,mul;
    ll attack=0;
    for(int i=0;i<n;i++){
        char c;
        cin >> c;
        if(c=='*'){
            ll x;
            cin >> x;
            mul.emplace_back(x);
        }else if(c=='+'){
            ll x;
            cin >> x;
            add.emplace_back(x);
        }else{
            attack++;
        }
    }
    if(!attack){
        cout << "*\n";
        exit(0);
    }
    sort(mul.rbegin(),mul.rend());
    sort(add.rbegin(),add.rend());
    add.insert(add.begin(),0LL);
    mul.insert(mul.begin(),1LL);
    for(int i=1;i<add.size();i++)add[i]=min(add[i-1]+add[i],L);
    for(int i=1;i<mul.size();i++)mul[i]=min(mul[i-1]*mul[i],L);
    ll prod=mul.back();
    ll sum=add.back();
    ll dmg=min(prod*sum,L);
    Info base{prod,dmg,min(attack*prod,L),min(attack*dmg,L)};
    vector<Info> dp(B);
    dp[0]=base;
    for(int i=1;i<B;i++)dp[i]=dp[i-1]+dp[i-1];
    Info cur{1,0,0,0};
    auto calc=[&](Info x){
        return p*x.mul2+x.add2;
    };
    ll ans=0;
    for(int i=B-1;i>=0;i--){
        if(calc(cur+dp[i])<h){
            cur=cur+dp[i];
            ans|=1LL<<i;
        }
    }
    if(calc(cur+base)<h){
        cout << "*\n";
        exit(0);
    }
    ans*=n;
    h-=calc(cur);
    p=min(p*cur.mul+cur.add,L);
    int ans2=n+1;
    for(int i=0;i<add.size();i++){
        ll pp=min(p+add[i],L);
        for(int j=0;j<mul.size();j++){
            ll ppp=min(pp*mul[j],L);
            for(int k=0;k<=attack;k++){
                if(ppp*k>=h){
                    ans2=min(ans2,i+j+k);
                }
            }
        }
    }
    assert(ans2<=n);
    cout << ans+ans2 << "\n";
}