#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int M=4*N;

int n,m;
int x[N],y[N];
vector<int> vx,vy;

void compress_point(){
    for(int i=1;i<=n;i++){
        if(x[i]&1)for(int j=-1;j<=2;j++)vx.emplace_back(x[i]+j);
        else for(int j=-2;j<=1;j++)vx.emplace_back(x[i]+j);
        vy.emplace_back(y[i]);
        vy.emplace_back(y[i]^1);
    }
    sort(vx.begin(),vx.end());
    sort(vy.begin(),vy.end());
    vx.erase(unique(vx.begin(),vx.end()),vx.end());
    vy.erase(unique(vy.begin(),vy.end()),vy.end());
    for(int i=1;i<=n;i++){
        x[i]=lower_bound(vx.begin(),vx.end(),x[i])-vx.begin()+1;
        y[i]=lower_bound(vy.begin(),vy.end(),y[i])-vy.begin()+1;
    }
}

vector<pair<int,int>> add[M],del[M];

void compress_range(vector<pair<int,int>> &v){
    sort(v.begin(),v.end());
    vector<pair<int,int>> res;
    for(auto [l,r]:v){
        if(!res.empty()&&res.back().second==l)res.back().second=r;
        else res.emplace_back(l,r);
    }
    swap(res,v);
}

void classify(){
    x[0]=x[n],y[0]=y[n];
    x[n+1]=x[1],y[n+1]=y[1];
    int st=1;
    for(int i=2;i<=n;i++)if(x[i]<x[st]||(x[i]==x[st]&&y[i]<y[st]))st=i;
    if(y[st+1]==y[st]){
        reverse(x,x+n+2);
        reverse(y,y+n+2);
    }
    for(int i=1;i<=n;i++)if(x[i]==x[i+1]){
        if(y[i+1]>y[i])add[x[i]].emplace_back(y[i],y[i+1]);
        else del[x[i]].emplace_back(y[i+1],y[i]);
    }
    for(int i=1;i<=4*n;i++){
        compress_range(add[i]);
        compress_range(del[i]);
        // cerr << "ADD " << i << ":\n";
        // for(auto [l,r]:add[i])cerr << "(" << l << "," << r << ") ";
        // cerr << "\n";
        // cerr << "DEL " << i << ":\n";
        // for(auto [l,r]:del[i])cerr << "(" << l << "," << r << ") ";
        // cerr << "\n";
    }
}

int ans;
multiset<pair<int,int>> fil[2];

void answer(){
    cout << (ans<vx.size()?vx[ans-1]:m);
    exit(0);
}

void insert(multiset<pair<int,int>> &f,int l,int r){
    if((r-l)%2)answer();
    f.emplace(l,r);
}

void process(){
    for(int i=1;i<=4*n+1;i++){
        auto &pre=fil[i&1];
        auto &cur=fil[i&1^1];
        if(pre.empty())ans=i;
        // for(auto [l,r]:cur)cerr<< "(" << l << "," << r << ") ";
        // if(!add[i].empty()||!del[i].empty())cerr << "\n";
        vector<pair<int,int>> to_add,to_add2;
        for(auto [l,r]:del[i]){
            auto it=cur.lower_bound(make_pair(l+1,0));
            if(it==cur.begin()||(--it)->second<r)answer();
        }
        for(auto [l,r]:del[i]){
            auto it=cur.lower_bound(make_pair(l+1,0));
            if(it!=cur.begin()&&(--it)->second>=r){
                if(it->first<l)to_add.emplace_back(it->first,l);
                if(it->second>r)to_add.emplace_back(r,it->second);
                cur.erase(it);
            }else{
                assert(!to_add.empty());
                auto [l2,r2]=to_add.back();
                to_add.pop_back();
                if(l2<l)to_add.emplace_back(l2,l);
                if(r2>r)to_add.emplace_back(r,r2);
            }
        }
        // for(auto [l,r]:to_add){
        //     cerr << "ADD*" << " : " << vy[l-1] << " " << vy[r-1] << " AT " << vx[i-1] << "\n";
        // }
        for(auto [l,r]:add[i]){
            auto it=cur.lower_bound(make_pair(l+1,0));
            if(it!=cur.begin()&&(--it)->second==l){
                l=it->first;
                cur.erase(it);
            }
            it=cur.lower_bound(make_pair(r,0));
            if(it!=cur.end()&&it->first==r){
                r=it->second;
                cur.erase(it);
            }
            if(!to_add2.empty()&&to_add2.back().second==l)to_add2.back().second=r;
            else to_add2.emplace_back(l,r);
        }
        // for(auto [l,r]:to_add2){
        //     cerr << "ADD" << " : " << vy[l-1] << " " << vy[r-1] << " AT " << vx[i-1] << "\n";
        // }
        for(auto e:to_add2)to_add.emplace_back(e);
        compress_range(to_add);
        for(auto [l,r]:to_add){
            // cerr << "ADD#" << " : " << vy[l-1] << " " << vy[r-1] << " AT " << vx[i-1] << "\n";
            insert(cur,l,r);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> x[i] >> y[i];
    compress_point();
    classify();
    process();
    cout << m;
}