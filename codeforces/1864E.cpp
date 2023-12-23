#include<bits/stdc++.h>

using namespace std;

//BINPOW
template<class T>
T binpow(T num,long long pow){
    T res=1;
    for(;pow;num*=num,pow>>=1)if(pow&1)res*=num;
    return res;
}
//--------------------------------------------------------
//MODULAR
long long mod=998244353;

struct modular{
    long long val;
    modular(long long x=0){ val=x%mod; if(val<0)val+=mod;}
    modular inv()const{return binpow(*this,mod-2);}
    modular& operator+=(const modular&o){val=(val+o.val)%mod; return *this;}
    modular& operator-=(const modular&o){val=(val-o.val+mod)%mod; return *this;}
    modular& operator*=(const modular&o){val=(val*o.val)%mod; return *this;}
    modular& operator/=(const modular&o){val=(val*o.inv().val)%mod; return *this;}
    modular& operator++(){return *this+=1;}
    modular& operator--(){return *this-=1;}
    modular operator++(int){modular ret=*this; *this+=1; return ret;}
    modular operator--(int){modular ret=*this; *this-=1; return ret;}
    friend modular operator+(const modular &lhs,const modular &rhs){return modular(lhs)+=rhs;}
    friend modular operator-(const modular &lhs,const modular &rhs){return modular(lhs)-=rhs;}
    friend modular operator*(const modular &lhs,const modular &rhs){return modular(lhs)*=rhs;}
    friend modular operator/(const modular &lhs,const modular &rhs){return modular(lhs)/=rhs;}
    friend istream &operator>>(istream &is,modular &o){long long x; is >> x; o=modular(x); return is;}
    friend ostream &operator<<(ostream &os,modular o){return os << o.val;}
};
typedef modular mint;
//--------------------------------------------------------

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    mint ans=0;
    map<int,vector<int>> mp;
    for(auto x:a){
        int num=0;
        mp[0].emplace_back(x);
        for(int i=30;i>=0;i--){
            if(x>>i&1){
                num+=1<<i;
                mp[num].emplace_back(x);
            }
        }
    }
    for(auto &[x,y]:mp)sort(y.begin(),y.end());
    for(auto x:a){
        int num=0,cnt=0;
        for(int i=30;i>=0;i--){
            if(x>>i&1){
                cnt++;
                int num2=1<<i;
                while(num2!=(num2&-num2))num2-=num2&-num2;
                int val=lower_bound(mp[num].begin(),mp[num].end(),num+num2)-mp[num].begin();
                ans+=(2*cnt+1)*val;
                num+=num2;
            }
        }
        ans+=(__builtin_popcount(x)+1)*(upper_bound(a.begin(),a.end(),x)-lower_bound(a.begin(),a.end(),x));
    }
    cout << ans/(mint(n)*n) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}