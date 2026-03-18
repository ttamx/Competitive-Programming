#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll LIM=1'000'000'000;

struct Bignum{
    int sgn;
    vector<ll> a;
    Bignum(ll x){
        if(x>0){
            sgn=1;
            a={x};
        }else if(x<0){
            sgn=-1;
            a={-x};
        }else{
            sgn=0;
            a={};
        }
    }
    Bignum operator-()const{
        Bignum o=*this;
        o.sgn*=-1;
        return o;
    }
    bool operator<(const Bignum &o)const{
        if(sgn!=o.sgn)return sgn<o.sgn;
        if(sgn==0)return false;
        if(a.size()!=o.a.size())return (a.size()<o.a.size())^(sgn==-1);
        for(int i=a.size()-1;i>=0;i--)if(a[i]!=o.a[i])return (a[i]<o.a[i])^(sgn==-1);
        return false;
    }
    Bignum& operator+=(const Bignum &o){
        if(o.sgn==0)return *this;
        if(sgn==0)return *this=o;
        if(sgn!=o.sgn)return *this-=(-o);
        int n=max(a.size(),o.a.size());
        a.resize(n+1);
        for(int i=0;i<n;i++){
            if(i<o.a.size())a[i]+=o.a[i];
            if(a[i]>=LIM)a[i]-=LIM,a[i+1]++;
        }
        while(!a.empty()&&a.back()==0)a.pop_back();
        if(a.empty())sgn=0;
        return *this;
    }
    Bignum& operator-=(const Bignum &o){
        if(o.sgn==0)return *this;
        if(sgn==0)return *this=(-o);
        if(sgn!=o.sgn)return *this+=(-o);
        if((sgn==1&&*this<o)||(sgn==-1&&o<*this)){
            *this=o-*this;
            sgn*=-1;
            return *this;
        }
        for(int i=0;i<o.a.size();i++)a[i]-=o.a[i];
        for(int i=0;i<a.size()-1;i++)if(a[i]<0)a[i]+=LIM,a[i+1]--;
        while(!a.empty()&&a.back()==0)a.pop_back();
        if(a.empty())sgn=0;
        return *this;
    }
    Bignum& operator*=(const ll k){
        for(auto &x:a)x*=k;
        for(int i=0;i<a.size();i++){
            if(a[i]>=LIM){
                if(i+1==a.size())a.emplace_back(0);
                a[i+1]+=a[i]/LIM;
                a[i]%=LIM;
            }
        }
        while(!a.empty()&&a.back()==0)a.pop_back();
        if(a.empty())sgn=0;
        return *this;
    }
    Bignum operator+(const Bignum &o)const{return Bignum(*this)+=o;}
    Bignum operator-(const Bignum &o)const{return Bignum(*this)-=o;}
    Bignum operator*(const ll &o)const{return Bignum(*this)*=o;}
    void print(){
        if(sgn==0)return void(cout << 0);
        string s="";
        for(int x:a){
            for(int i=0;i<9;i++){
                s.push_back('0'+x%10);
                x/=10;
            }
        }
        while(s.back()=='0')s.pop_back();
        if(sgn==-1)s.push_back('-');
        reverse(s.begin(),s.end());
        cout << s;
    }
};

struct Info{
    Bignum t,x,y,z;
    Info():t(0),x(0),y(0),z(0){}
    Info(ll t,ll x,ll y,ll z):t(t),x(x),y(y),z(z){}
};

map<string,Info> var;
map<string,int> num;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    num["zero"]=0;
    num["one"]=1;
    num["two"]=2;
    num["three"]=3;
    num["four"]=4;
    num["five"]=5;
    num["six"]=6;
    num["seven"]=7;
    num["eight"]=8;
    num["nine"]=9;

    var["right"]=Info{1,+1,0,0};
    var["left"]=Info{1,-1,0,0};
    var["forw"]=Info{1,0,+1,0};
    var["back"]=Info{1,0,-1,0};
    var["up"]=Info{1,0,0,+1};
    var["down"]=Info{1,0,0,-1};

    vector<string> a;
    for(string s;cin >> s;)a.emplace_back(s);
    int n=a.size();
    Info ans{0,0,0,0};
    for(int i=0;i<n;i++){
        if(i+1<n&&a[i+1]=="{"){
            assert(!var.count(a[i]));
            Info &cur=var[a[i]];
            cur=Info{0,0,0,0};
            i+=2;
            while(i<n&&a[i]!="}"){
                int mul=1;
                if(num.count(a[i])){
                    mul=num[a[i]];
                    i++;
                }
                assert(i<n);
                assert(var.count(a[i]));
                cur.t+=var[a[i]].t*mul;
                cur.x+=var[a[i]].x*mul;
                cur.y+=var[a[i]].y*mul;
                cur.z+=var[a[i]].z*mul;
                i++;
            }
            assert(i<n);
            assert(a[i]=="}");
        }else{
            int mul=1;
            if(num.count(a[i])){
                mul=num[a[i]];
                i++;
            }
            assert(i<n);
            assert(var.count(a[i]));
            ans.t+=var[a[i]].t*mul;
            ans.x+=var[a[i]].x*mul;
            ans.y+=var[a[i]].y*mul;
            ans.z+=var[a[i]].z*mul;
        }
    }
    ans.t.print();
    cout << " ";
    ans.x.print();
    cout << " ";
    ans.y.print();
    cout << " ";
    ans.z.print();
    cout << "\n";
}