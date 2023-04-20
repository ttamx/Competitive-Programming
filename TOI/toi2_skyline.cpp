#include<bits/stdc++.h>

using namespace std;

const int N=3005;
const int M=260;

int n,st=255;
vector<int> add[M],del[M];
multiset<int> ms;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        int l,h,r;
        cin >> l >> h >> r;
        st=min(st,l);
        add[l].emplace_back(h);
        del[r].emplace_back(h);
    }
    int pre=-1;
    ms.emplace(0);
    for(int i=st;i<=255;i++){
        for(auto x:add[i])ms.emplace(x);
        for(auto x:del[i])ms.erase(ms.find(x));
        int res=*ms.rbegin();
        if(res!=pre)cout << i << " " << res << " ";
        pre=res;
    }
}