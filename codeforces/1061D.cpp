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
long long mod=1e9+7;

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

typedef long long ll;

int n;
ll x,y,d;
mint ans=0;
vector<pair<int,int>> vec;
priority_queue<int,vector<int>,greater<int>> pq;
priority_queue<int> pq2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> x >> y;
    for(int i=0;i<n;i++){
        int l,r;
        cin >> l >> r;
        vec.emplace_back(l,r);
    }
    sort(vec.begin(),vec.end());
    for(auto [l,r]:vec){
        while(!pq.empty()&&pq.top()<l){
            pq2.emplace(pq.top());
            pq.pop();
        }
        if(!pq2.empty()&&(l-pq2.top())*y<=x){
            ans+=(r-pq2.top())*y;
            pq2.pop();
        }else{
            ans+=(r-l)*y+x;
        }
        pq.emplace(r);
    }
    cout << ans;
}