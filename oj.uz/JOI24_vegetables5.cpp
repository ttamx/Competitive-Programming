#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

const int N=3e5+5;
const int INF=INT_MAX/2;

int n;
int a[3*N],b[N],c[N],pos[3*N];
bool lo[3*N],d1[3*N],d2[3*N];

struct Info{
    int sum,pre,suf,mx;
    static Info unit(){
        return {0,-INF,-INF,-INF};
    }
    friend Info operator+(const Info &l,const Info &r){
        return {l.sum+r.sum,max(l.pre,l.sum+r.pre),max(r.suf,r.sum+l.suf),max({l.mx,r.mx,l.suf+r.pre})};
    }
};

struct Stack{
    using P = pair<Info,int>;
    stack<P> s;
    stack<Info> p;
    bool empty(){return s.empty();}
    P front(){return s.top();}
    P back(){return s.top();}
    void push_front(Info x,int v){
        s.emplace(x,v);
        if(p.empty())p.emplace(x);
        else p.emplace(x+p.top());
    }
    void push_back(Info x,int v){
        s.emplace(x,v);
        if(p.empty())p.emplace(x);
        else p.emplace(p.top()+x);
    }
    void push_front(P x){push_front(x.first,x.second);}
    void push_back(P x){push_back(x.first,x.second);}
    void pop_back(){s.pop();p.pop();}
    void pop_front(){s.pop();p.pop();}
    Info query(){return p.empty()?Info::unit():p.top();}
};

struct Deque{
    using P = pair<Info,int>;
    deque<P> dq;
    stack<Info> l,r;
    void rebalance(bool left){
        int s=dq.size();
        int m=(s+left)/2;
        while(!l.empty())l.pop();
        while(!r.empty())r.pop();
        {
            Info sum=Info::unit();
            for(int i=m-1;i>=0;i--){
                sum=dq[i].first+sum;
                l.emplace(sum);
            }
        }
        {
            Info sum=Info::unit();
            for(int i=m;i<s;i++){
                sum=sum+dq[i].first;
                r.emplace(sum);
            }
        }
    }
    bool empty(){return dq.empty();}
    int size(){return dq.size();};
    P front(){return dq.front();}
    P back(){return dq.back();}
    void push_front(Info x,int v){
        dq.emplace_front(x,v);
        if(l.empty())l.emplace(x);
        else l.emplace(x+l.top());
    }
    void push_back(Info x,int v){
        dq.emplace_back(x,v);
        if(r.empty())r.emplace(x);
        else r.emplace(r.top()+x);
    }
    void push_front(P x){push_front(x.first,x.second);}
    void push_back(P x){push_back(x.first,x.second);}
    void pop_front(){
        assert(!dq.empty());
        if(l.empty())rebalance(true);
        dq.pop_front();
        l.pop();
    }
    void pop_back(){
        assert(!dq.empty());
        if(r.empty())rebalance(false);
        dq.pop_back();
        r.pop();
    }
    Info query(){
        if(dq.empty())return Info::unit();
        if(l.empty())return r.top();
        if(r.empty())return l.top();
        return l.top()+r.top();
    }
};

void calc(int *b,bool *d,int k){
    int st=0,ed=0;
    Stack q1,q3;
    Deque q2;
    auto work=[&](int i){
        if(lo[i]){
            while(!q1.empty()&&q1.back().second>=pos[i]){
                q2.push_front(q1.back());
                q1.pop_back();
            }
            while(!q2.empty()&&q2.front().second<pos[i]){
                q1.push_back(q2.front());
                q2.pop_front();
            }
            while(!q3.empty()&&q3.front().second<pos[i]){
                q1.push_back(q3.front());
                q3.pop_front();
            }
        }else{
            while(!q3.empty()&&q3.front().second<=pos[i]){
                q2.push_back(q3.front());
                q3.pop_front();
            }
            while(!q2.empty()&&q2.back().second>pos[i]){
                q3.push_front(q2.back());
                q2.pop_back();
            }
            while(!q1.empty()&&q1.back().second>pos[i]){
                q3.push_front(q1.back());
                q1.pop_back();
            }
        }
    };
    for(int i=0;i<3*n;i++){
        while(st<n&&b[st]<a[i]-k)st++;
        while(st>0&&b[st-1]>=a[i]-k)st--;
        while(ed<n&&b[ed]<=a[i]+k)ed++;
        while(ed>0&&b[ed-1]>a[i]+k)ed--;
        work(i);
        Info cur{1,1-ed,1+st,1+st-ed};
        if(lo[i])q2.push_front(cur,pos[i]);
        else q2.push_back(cur,pos[i]);
        if(i>=n){
            work(i-n);
            if(lo[i-n])q2.pop_front();
            else q2.pop_back();
            d[i]=(q1.query()+q2.query()+q3.query()).mx<=0;
        }
    }
}

bool check(int k){
    calc(b,d1,k);
    calc(c,d2,k);
    for(int i=n;i<2*n;i++){
        if((d1[i]&&d2[i+n])||(d2[i]&&d1[i+n])){
            return true;
        }
    }
    return false;
}

int main(){
    cin >> n;
    vector<pair<int,int>> vals;
    for(int i=0;i<2*n;i++){
        cin >> a[i];
        vals.emplace_back(a[i],i>n?~i:i);
    }
    sort(vals.begin(),vals.end());
    for(int i=0;i<2*n;i++){
        int j=vals[i].second;
        pos[j<0?~j:j]=i;
    }
    for(int i=2*n;i<3*n;i++){
        a[i]=a[i-2*n];
        pos[i]=pos[i-2*n];
    }
    for(int i=0;i<2*n;i++){
        lo[i]=pos[i]<pos[i+n];
    }
    for(int i=2*n;i<3*n;i++){
        lo[i]=lo[i-2*n];
    }
    for(int i=0;i<n;i++){
        cin >> b[i];
    }
    for(int i=0;i<n;i++){
        cin >> c[i];
    }
    sort(b,b+n);
    sort(c,c+n);
    int l=0,r=1'000'000'000;
    while(l<r){
        int m=(l+r)/2;
        if(check(m))r=m;
        else l=m+1;
    }
    cout << l << "\n";
}