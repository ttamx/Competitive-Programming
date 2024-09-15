#include<bits/stdc++.h>

using namespace std;

// smawck for max
template<class F>
std::vector<int> smawck(F f, const std::vector<int> &rows, const std::vector<int> &cols) {
    std::vector<int> ans(rows.size(), -1);
    if((int) std::max(rows.size(), cols.size()) <= 2) {
        for(int i = 0; i < (int) rows.size(); i++) {
            for(auto j : cols) {
                if(ans[i] == -1 || f(rows[i], ans[i], j)) {
                    ans[i] = j;
                }
            }
        }
    } else if(rows.size() < cols.size()) {
        // reduce
        std::vector<int> st;
        for(int j : cols) {
            while(1) {
                if(st.empty()) {
                    st.push_back(j);
                    break;
                } else if(f(rows[(int) st.size() - 1], st.back(), j)) {
                    st.pop_back();
                } else if(st.size() < rows.size()) {
                    st.push_back(j);
                    break;
                } else {
                    break;
                }
            }
        }
        ans = smawck(f, rows, st);
    } else {
        std::vector<int> newRows;
        for(int i = 1; i < (int) rows.size(); i += 2) {
            newRows.push_back(rows[i]);
        }
        auto otherAns = smawck(f, newRows, cols);
        for(int i = 0; i < (int) newRows.size(); i++) {
            ans[2*i+1] = otherAns[i];
        }
        for(int i = 0, l = 0, r = 0; i < (int) rows.size(); i += 2) {
            if(i+1 == (int) rows.size()) r = (int) cols.size();
            while(r < (int) cols.size() && cols[r] <= ans[i+1]) r++;
            ans[i] = cols[l++];
            for(; l < r; l++) {
                if(f(rows[i], ans[i], cols[l])) {
                    ans[i] = cols[l];
                }
            }
            l--;
        }
    }
    return ans;
}

// max smawck
// F(i, j, k) checks if M[i][j] <= M[i][k]
// another interpretations is: 
// F(i, j, k) checks if M[i][k] is at least as good as M[i][j]
// higher == better
// when comparing 2 columns as vectors
// for j < k, column j can start better than column k
// as soon as column k is at least as good, it's always at least as good
template<class F>
std::vector<int> smawck(F f, int n, int m) {
    std::vector<int> rows(n), cols(m);
    for(int i = 0; i < n; i++) rows[i] = i;
    for(int i = 0; i < m; i++) cols[i] = i;
    return smawck(f, rows, cols);
}

template<class T>
std::vector<T> MaxConvolutionWithConvexShape(std::vector<T> anyShape, const std::vector<T> &convexShape) {
    if((int) convexShape.size() <= 1) return anyShape;
    if(anyShape.empty()) anyShape.push_back(0);
    int n = (int) anyShape.size(), m = (int) convexShape.size();
    auto function = [&](int i, int j) {
        return anyShape[j] + convexShape[i-j];
    };
    auto comparator = [&](int i, int j, int k) {
        if(i < k) return false;
        if(i - j >= m) return true;
        return function(i, j) <= function(i, k);
    };
    const std::vector<int> best = smawck(comparator, n + m - 1, n);
    std::vector<T> ans(n + m - 1);
    for(int i = 0; i < n + m - 1; i++) {
        ans[i] = function(i, best[i]);
    }
    return ans;
}

using ll = long long;

const ll LINF=1e18;

template<class Node>
struct SegTree{
    int n;
    vector<Node> t;
    SegTree(int n=0,Node v=Node()){init(n,v);}
    template<class T>
    SegTree(const vector<T> &a){init(a);}
    void init(int n,Node v=Node()){init(vector(n,v));}
    template<class T>
    void init(const vector<T> &a){
        n=a.size();
        t.assign(4<<31-__builtin_clz(n),Node());
        function<void(int,int,int)> build=[&](int l,int r,int i){
            if(l==r)return void(t[i]=a[l]);
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
    void modify(int l,int r,int i,int x,const Node &v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        modify(l,m,i*2,x,v);
        modify(m+1,r,i*2+1,x,v);
        pull(i);
    }
    void modify(int x,const Node &v){
        modify(0,n-1,1,x,v);
    }
    template<class T>
    void update(int l,int r,int i,int x,const T &v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i].apply(l,r,v));
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        pull(i);
    }
    template<class T>
    void update(int x,const T &v){
        update(0,n-1,1,x,v);
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
    template<class F>
    int findfirst(int l,int r,int i,int x,int y,const F &f){
        if(y<l||r<x||!f(t[i]))return -1;
        if(l==r)return l;
        int m=(l+r)/2;
        int res=findfirst(l,m,i*2,x,y,f);
        if(res==-1)res=findfirst(m+1,r,i*2+1,x,y,f);
        return res;
    }
    template<class F>
    int findfirst(int x,int y,const F &f){
        return findfirst(0,n-1,1,x,y,f);
    }
    template<class F>
    int findlast(int l,int r,int i,int x,int y,const F &f){
        if(y<l||r<x||!f(t[i]))return -1;
        if(l==r)return l;
        int m=(l+r)/2;
        int res=findlast(m+1,r,i*2+1,x,y,f);
        if(res==-1)res=findlast(l,m,i*2,x,y,f);
        return res;
    }
    template<class F>
    int findlast(int x,int y,const F &f){
        return findlast(0,n-1,1,x,y,f);
    }
};
struct MaxNode{
    ll val;
    MaxNode():val(0LL){}
    MaxNode(ll x):val(x){}
    void apply(int l,int r,ll x){
        val+=x;
    }
    friend MaxNode operator+(const MaxNode &lhs,const MaxNode &rhs){
        return MaxNode(max(lhs.val,rhs.val));
    }
};

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    int offset=0;
    map<int,int> cnt;
    for(auto &x:b){
        cin >> x;
        offset+=x;
        cnt[x]++;
    }
    int m=cnt.size();
    vector<ll> 
    SegTree<MaxNode> seg(poly.back());
    while(q--){
        int l,r;
        cin >> l >> r;
        ll val1=seg.query(l+offset,r+offset).val;
        ll val2=seg.query(offset-r,offset-l).val;
        cout << max(val1,val2) << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        runcase();
    }
}