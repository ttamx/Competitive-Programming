#include<bits/stdc++.h>

using namespace std;

mt19937 rng(998244353);

struct Segtree{
    struct Node{
        int mn,mx;
        Node():mn(INT_MAX),mx(INT_MIN){}
        Node(int v):mn(v),mx(v){}
        Node(int _mn,int _mx):mn(_mn),mx(_mx){}
        friend Node operator+(const Node &lhs,const Node &rhs){
            return Node(min(lhs.mn,rhs.mn),max(lhs.mx,rhs.mx));
        }
    };
    int n;
    vector<Node> t;
    Segtree(const vector<int> &a){
        init(a);
    }
    void init(const vector<int> &a){
        n=a.size();
        t.assign(4<<(31-__builtin_clz(n)),Node());
        function<void(int,int,int)> build=[&](int l,int r,int i){
            if(l==r)return void(t[i]=Node(a[l]));
            int m=(l+r)/2;
            build(l,m,i*2);
            build(m+1,r,i*2+1);
            pull(i);
        };
        build(0,n-1,1);
    }
    void pull(int i){
        t[i]=t[i*2]+t[i*2+1];
    }
    void modify(int l,int r,int i,int x,int v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=Node(v));
        int m=(l+r)/2;
        modify(l,m,i*2,x,v);
        modify(m+1,r,i*2+1,x,v);
        pull(i);
    }
    void modify(int x,int v){
        modify(0,n-1,1,x,v);
    }
    Node query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return Node();
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    Node query(int x,int y){
        return query(0,n-1,1,x,y);
    }
};

int rnd(int x){
    return rng()%x;
}

int rnd(int l,int r){
    return l+rnd(r-l+1);
}

double rand_double(){
    const int X=1<<30;
    return 1.0*(rng()%X)/X;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    auto start=chrono::system_clock::now();
    int n,k;
    cin >> n >> k;
    vector<pair<int,int>> a(k);
    for(auto &[l,r]:a)cin >> l >> r,l--,r--;
    vector<int> p(n);
    iota(p.begin(),p.end(),0);
    shuffle(p.begin(),p.end(),rng);
    Segtree s(p);
    auto get_score=[&](){
        int res=0;
        for(auto &[l,r]:a){
            auto tmp=s.query(l,r);
            res+=tmp.mx-tmp.mn;
        }
        return res;
    };
    int cur_score=get_score();
    int max_score=cur_score;
    auto ans=p;
    while(chrono::duration<double>(chrono::system_clock::now()-start).count()<=2.9){
        int x=rnd(n),y=rnd(n);
        if(x==y)continue;
        swap(p[x],p[y]);
        s.modify(x,p[x]);
        s.modify(y,p[y]);
        int new_score=get_score();
        if(new_score>cur_score){
            cur_score=new_score;
            if(cur_score>max_score){
                max_score=cur_score;
                ans=p;
            }
        }else if(rand_double()<=exp(4.0*(new_score-cur_score))){
            cur_score=new_score;
        }else{
            swap(p[x],p[y]);
            s.modify(x,p[x]);
            s.modify(y,p[y]);
        }
    }
    for(auto x:ans)cout << x+1 << " ";
}