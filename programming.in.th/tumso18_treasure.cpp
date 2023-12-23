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
long long mod=98765431;

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

struct matrix{
    mint a[3][3]={};
    friend matrix operator*(matrix a,matrix b){
        matrix c;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                c.a[i][j]=0;
                for(int k=0;k<3;k++){
                    c.a[i][j]+=a.a[i][k]*b.a[k][j];
                }
            }
        }
        return c;
    }
}I,dp[60];

int q;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=0;i<3;i++)I.a[i][i]=1;
    dp[0].a[0][0]=dp[0].a[0][1]=dp[0].a[0][2]=1;
    dp[0].a[1][0]=dp[0].a[1][2]=1;
    dp[0].a[2][0]=dp[0].a[2][1]=1;
    for(int i=1;i<60;i++)dp[i]=dp[i-1]*dp[i-1];
    cin >> q;
    while(q--){
        long long n;
        cin >> n;
        n--;
        matrix res=I;
        for(int i=0;i<60;i++){
            if(n&(1ll<<i)){
                res=res*dp[i];
            }
        }
        mint ans=0;
        for(int i=0;i<3;i++)for(int j=0;j<3;j++)ans+=res.a[i][j];
        cout << ans << "\n";
    }
}