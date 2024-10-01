#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const ll INF=1e18;

struct Fenwick{
    ll t[N];
    void update(int i,ll v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    ll query(int i){
        ll res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f;

struct Line{
    ll m,c;
    mutable ll p;
    int i;
    Line(){}
    Line(ll _m,ll _c,int _i):m(_m),c(_c),i(_i){}
    ll getc()const{
        return c+f.query(i);
    }
    bool operator<(const Line &o)const{
        return m<o.m||(m==o.m&&i<o.i);
    }
    bool operator<(const ll &x)const{
        return p<x;
    }
};

struct LineContainer:multiset<Line,less<>>{
    ll div(ll a,ll b){
        return a/b-((a^b)<0&&a%b!=0);
    }
    bool isect(iterator x,iterator y){
        if(y==end())return x->p=INF,false;
        if(x->m==y->m)x->p=x->getc()>=y->getc()?INF:-INF;
        else x->p=div(x->getc()-y->getc(),y->m-x->m);
        return x->p>=y->p;
    }
    void add_line(Line v){
        auto x=insert(v),y=next(x);
        while(isect(x,y))y=erase(y);
        if((y=x)!=begin()&&isect(--x,y))isect(x,erase(y));
        while((y=x)!=begin()&&(--x)->p>=y->p)isect(x,erase(y));
    }
    void compress(Line v){
        auto x=lower_bound(v),y=x;
        while((y=x)!=begin()&&(--x)->p>=y->p)isect(x,erase(y));
    }
    ll query(ll x){
        assert(!empty());
        auto l=*lower_bound(x);
        return l.m*x+l.getc();
    }
}cht;

int n;
ll a[N],b[N];
int id[N];
vector<pair<int,int>> vals;
multiset<int> s;
Line lines[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        b[i]=a[i];
        vals.emplace_back(a[i],i);
    }
    sort(b+1,b+n+1);
    sort(vals.begin(),vals.end());
    for(int i=0;i<n;i++){
        id[vals[i].second]=i+1;
    }
    for(int i=1;i<=n;i++){
        lines[i]=Line(b[i],b[i]*b[i],i);
    }
    s.emplace(id[1]);
    cht.add_line(lines[id[1]]);
    for(int _i=2;_i<=n;_i++){
        int i=id[_i];
        auto it=s.emplace(i);
        if(next(it)!=s.end()&&it!=s.begin()){
            f.update(*next(it),-b[*prev(it)]*b[*next(it)]);
        }
        if(next(it)!=s.end()){
            f.update(*next(it),b[i]*b[*next(it)]);
        }
        if(it!=s.begin()){
            f.update(i,b[i]*b[*prev(it)]);
        }
        if(next(it)!=s.end()){
            cht.compress(lines[*it]);
        }
        cht.add_line(lines[i]);
        ll l,r;
        cin >> l >> r;
        ll res=cht.query(-r);
        ll mn=b[*s.begin()];
        cout << max(0LL,(res+mn-1)/mn) << "\n";
    }
}