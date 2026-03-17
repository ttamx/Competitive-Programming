#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;

int q,n;
vector<tuple<int,int,int,int>> qr;
int pos[N],s[N];
set<int> st;

struct Segtree{
    void update(int l,int r,int i,int x,int y,ll v){

    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed;
    cin >> q;
    qr.resize(q);
    for(auto &[op,x,y,z]:qr){
        cin >> op;
        if(op==1){
            cin >> x >> y;
            pos[n++]=x;
        }else if(op==2)cin >> x;
        else cin >> x >> y >> z;
    }
    sort(pos,pos+n);
    n=unique(pos,pos+n)-pos;
    pos[n]=1e9+1;
    st.emplace(n);
    for(auto &[op,x,y,z]:qr){
        if(op==3){
            if(z==0){
                cout << x << "\n";
                continue;
            }
            auto it=st.lower_bound(x);
            int r=*it;
            int p=min(y+1,pos[r]);
            if(it!=st.begin()){
                int l=*prev(it);
                int d=*it-x;
                if(z+1LL*s[l]*d<=0){
                    cout << x+double(z)/-s[l] << "\n";
                    continue;
                }
            }
            x=*it;
        }else{
            x=lower_bound(pos,pos+n,x)-pos;
            auto it=st.lower_bound(x);
            if(op==1){
                int r=*it;
                s[x]=y;
                if(it!=st.begin()){
                    int l=*prev(it);
                    seg.update(0,n-1,1,l,n-1,-1LL*(r-x)*s[l]);
                }
                seg.update(0,n-1,1,x,n-1,1LL*(r-x)*s[x]);
            }else{
                it=st.erase(it);
                int r=*it;
                if(it!=st.begin()){
                    int l=*prev(it);
                    seg.update(0,n-1,1,l,n-1,1LL*(r-x)*s[l]);
                }
                seg.update(0,n-1,1,x,n-1,-1LL*(r-x)*s[x]);
            }
        }
    }
    cout << "DONE\n";
}