#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    vector<int> xs,ys;
    for(auto &[x,y]:a){
        cin >> x >> y;
        xs.emplace_back(x);
        ys.emplace_back(y);
    }
    sort(xs.begin(),xs.end());
    sort(ys.begin(),ys.end());
    vector<vector<int>> pts(n);
    for(auto &[x,y]:a){
        x=lower_bound(xs.begin(),xs.end(),x)-xs.begin();
        y=lower_bound(ys.begin(),ys.end(),y)-ys.begin();
        pts[x].emplace_back(y);
    }
    int ax,ay;
    auto check=[&](int k){
        Fenwick<int> fl(n),fr(n);
        for(int i=0;i<n;i++){
            for(auto x:pts[i]){
                fr.update(x,+1);
            }
        }
        for(int i=n-1;i>=0;i--){
            for(auto x:pts[i]){
                fl.update(x,+1);
                fr.update(x,-1);
            }
            int cut=max(fl.find(k-1),fr.find(k-1));
            int mn=min(fl.query(cut),fr.query(cut));
            mn=min({mn,fl.query(cut+1,n-1),fr.query(cut+1,n-1)});
            ax=i,ay=cut;
            if(mn>=k)return true;
        }
        return false;
    };
    check(1);
    int l=0,r=n;
    while(l<r){
        int m=(l+r+1)/2;
        if(check(m))l=m;
        else r=m-1;
    }
    check(l);
    cout << l << "\n";
    if(l==0){
        cout << 0 << " " << 0 << "\n";
    }else{
        cout << xs[ax] << " " << ys[ay]+1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}