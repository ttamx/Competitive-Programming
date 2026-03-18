#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = complex<ll>;

ll cross(P a,P b){
    return imag(conj(a)*b);
}

ll cross(P a,P b,P o){
    return cross(a-o,b-o);
}

P get(){
    ll x,y;
    cin >> x >> y;
    return P(x,y);
}

void print(P p){
    cout << real(p) << " " << imag(p) << "\n";
}

void runcase(){
    P st=get(),ed=get();
    int n;
    cin >> n;
    vector<pair<P,P>> a;
    vector<P> chain1{st},chain2{st};
    int ptr1=0,ptr2=0;
    for(int i=0;i<n;i++){
        ll x,l,r;
        cin >> x >> l >> r;
        a.emplace_back(P(x,l),P(x,r));
    }
    a.emplace_back(ed,ed);
    for(auto [p1,p2]:a){
        while(chain1.size()-ptr1>=2&&cross(chain1.back(),p1,chain1.end()[-2])>=0){
            chain1.pop_back();
        }
        chain1.emplace_back(p1);
        while(chain2.size()-ptr2>=2&&cross(chain2.back(),p2,chain2.end()[-2])<=0){
            chain2.pop_back();
        }
        chain2.emplace_back(p2);
        P piv=chain1[ptr1];
        if(cross(chain1[ptr1+1],chain2[ptr2+1],piv)<0){
            int sz1=chain1.size()-ptr1;
            int sz2=chain2.size()-ptr2;
            if(sz1==2){
                assert(sz2>2);
                chain1.pop_back();
                while(cross(p1,chain2[ptr2+1],piv)<0){
                    assert(ptr2+1<chain2.size());
                    chain1.emplace_back(piv=chain2[++ptr2]);
                }
                ptr1=chain1.size()-1;
                chain1.emplace_back(p1);
            }else if(sz2==2){
                assert(sz1>2);
                chain2.pop_back();
                while(cross(chain1[ptr1+1],p2,piv)<0){
                    assert(ptr1+1<chain1.size());
                    chain2.emplace_back(piv=chain1[++ptr1]);
                }
                ptr2=chain2.size()-1;
                chain2.emplace_back(p2);
            }else assert(false);
        }
    }
    for(auto p:chain1)print(p);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}