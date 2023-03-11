#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

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
    friend ostream &operator<<(ostream &os,modular &o){return os << o.val;}
};
typedef modular mint;
//--------------------------------------------------------

struct mat{
    mint m[2][2]={{1,0},{0,1}};
    friend mat operator*(mat a,mat b){
        mat c;
        for(int i=0;i<2;i++)for(int j=0;j<2;j++){
            c.m[i][j]=0;
            for(int k=0;k<2;k++)c.m[i][j]+=a.m[i][k]*b.m[k][j];
        }
        return c;
    }
};

void runcase(){
    ll n;
    cin >> n;
    mint val=-n;
    n--;
    mat ans,res;
    res.m[0][0]=0;
    res.m[0][1]=-1;
    res.m[1][0]=1;
    res.m[1][1]=3;
    while(n){
        if(n&1)ans=ans*res;
        res=res*res;
        n>>=1;
    }
    val+=ans.m[1][1];
    cout << val << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}