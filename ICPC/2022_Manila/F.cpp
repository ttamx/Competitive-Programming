#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,int> p2;

const int N=2e5+5;

int n;
ll w[N],sum;
set<int> s;
set<p2> s2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> w[i];
        s.emplace(i);
        s2.emplace(w[i],i);
        sum+=w[i];
    }
    for(int i=1;i<=n;i++){
        auto [mx,id]=*s2.lower_bound(p2(s2.rbegin()->first,0));
        if(mx*2>sum)id=s2.begin()->second;
        cout << id << " " << w[id] << "\n";
        s2.erase(p2(w[id],id));
        sum-=w[id];
        auto it=s.erase(s.find(id));
        if(it!=s.end()){
            int r=*it;
            sum+=w[id]/2;
            s2.erase(p2(w[r],r));
            w[r]+=w[id]/2;
            s2.emplace(p2(w[r],r));
        }
        if(it!=s.begin()){
            int l=*prev(it);
            sum+=w[id]/2;
            s2.erase(p2(w[l],l));
            w[l]+=w[id]/2;
            s2.emplace(p2(w[l],l));
        }
    }
}