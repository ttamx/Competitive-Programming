#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/min-idx-add.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(m)),b(n,vector<int>(m));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    vector<int> c;
    for(auto &v:b){
        for(auto &x:v){
            cin >> x;
            c.emplace_back(x);
        }
    }
    int curi=0,curj=0,cur_pos=0;
    auto next_pos=[&](){
        curj++;
        if(curj==m){
            curi++;
            curj=0;
        }
        cur_pos++;
    };
    vector<int> pos(n*m,-1);
    auto answer=[&](int k){
        if(k==0){
            reverse(c.begin(),c.end());
            cout << c.size() << "\n";
            for(auto x:c){
                cout << 1 << " " << x << "\n";
            }
            return;
        }
        vector<pair<int,int>> ans;
        int last=n*m-1;
        vector<queue<int>> vals(k);
        for(int i=k-1;i>=0;i--){
            while(last>pos[i]){
                vals[i].emplace(last);
                last--;
            }
            last=pos[i]-1;
        }
        Fenwick<int> f(k);
        LazySegmentTree<MinAddIdxAction<int,int,false>> seg(k,[&](int i){
            if(vals[i].empty())return make_pair(INF,-1);
            int bound=(i/m+1)*m-1;
            return make_pair(bound-i,i);
        });
        for(int i=1;i<k;i++){
            f.update(i,1);
        }
        while(true){
            auto [mn,idx]=seg.query(0,k-1);
            if(idx==-1)break;
            if(mn>0){
                for(int i=0;i<mn;i++){
                    ans.emplace_back(0,last);
                    last--;
                }
                f.update(0,mn);
                seg.update(0,k-1,-mn);
            }
            int cur=f.query(idx);
            assert(cur%m==m-1);
            int row=cur/m;
            assert(!vals[idx].empty());
            ans.emplace_back(row+1,vals[idx].front());
            if(idx<k){
                f.update(idx+1,+1);
                seg.update(idx+1,k,-1);
            }
            vals[idx].pop();
            if(vals[idx].empty()){
                seg.modify(idx,make_pair(INF,-1));
            }
        }
        while(last>=0){
            ans.emplace_back(0,last);
            last--;
        }
        cout << ans.size() << "\n";
        for(auto [x,y]:ans){
            cout << x+1 << " " << c[y] << "\n";
        }
    };
    int match=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            while(curi<n&&b[curi][curj]!=a[i][j]){
                next_pos();
            }
            if(curi>=n){
                answer(i*m+j);
                return;
            }
            pos[i*m+j]=cur_pos;
            match++;
            next_pos();
            while(curi==i&&j+1<m){
                j++;
                if(a[i][j]!=b[curi][curj]){
                    answer(i*m);
                    return;
                }
                pos[i*m+j]=cur_pos;
                match++;
                next_pos();
            }
        }
    }
    cout << 0 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}