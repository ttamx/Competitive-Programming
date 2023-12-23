#include<bits/stdc++.h>

using namespace std;

int n,p,q;
map<int,int> mpl,mpr;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> p;
    mpl[0]=mpr[0]=0;
    for(int i=1;i<=p;i++){
        int t,w;
        cin >> t >> w;
        if(t==1){
            mpl[1]^=1;
            mpl[w+1]^=1;
        }else{
            mpr[w]^=1;
        }
    }
    int pre=0;
    for(auto &[x,y]:mpl)pre=y=y^pre;
    pre=0;
    for(auto &[x,y]:mpr)pre=y=y^pre;
    cin >> q;
    while(q--){
        int x,y;
        cin >> x >> y;
        cout << (prev(mpl.upper_bound(max(x,y)))->second^prev(mpr.upper_bound(min(x,y)))->second) << "\n";
    }
}