#include<bits/stdc++.h>

using namespace std;

mt19937 rng(1276376);

const int X=100'000;
const int K=199;
const double EPS=1e-6;
const bool AUTO=false;

int ansx=40000;
int ansy=60000;
int ansr=30000;

double ask(int x1,int y1,int x2,int y2){
    if(AUTO){
        if(x1==x2){
            return abs(ansx-x1)<ansr;
        }
        if(y1==y2){
            return abs(ansy-y1)<ansr;
        }
        assert(false);
    }
    cout << "query " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    double res;
    cin >> res;
    return res;
}

void answer(int x,int y,int r){
    cout << "answer " << x << " " << y << " " << r << endl;  
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<int> cand;
    for(int i=0;i<=X;i+=K){
        cand.emplace_back(i);
    }
    shuffle(cand.begin(),cand.end(),rng);
    int x=-1;
    for(auto val:cand){
        if(ask(val,0,val,X)>EPS){
            x=val;
            break;
        }
    }
    assert(x!=-1);
    int le,ri,up;
    {
        int l=0,r=x-1;
        while(l<r){
            int m=(l+r+1)/2;
            if(ask(m,0,m,X)>EPS)r=m-1;
            else l=m;
        }
        le=l;
    }
    {
        int l=x+1,r=X;
        while(l<r){
            int m=(l+r)/2;
            if(ask(m,0,m,X)>EPS)l=m+1;
            else r=m;
        }
        ri=l;
    }
    int rad=ri-le;
    assert(rad%2==0);
    rad/=2;
    {
        int l=0,r=X;
        while(l<r){
            int m=(l+r+1)/2;
            if(ask(le+rad,0,le+rad,m)>EPS)r=m-1;
            else l=m;
        }
        up=l;
    }
    answer(le+rad,up+rad,rad);
}