#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=3e5+5;
const int INF=INT_MAX/2;

vector<int> divisor[N];
int st[N];
int mob[N];
vector<int> pos[N];
vector<int> all_pos;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto x:a){
        for(auto d:divisor[x]){
            st[d]=n;
            pos[d].clear();
        }
    }
    all_pos.clear();
    int base=0,diff=0;
    for(int i=0;i<n;i++){
        int ptr=n;
        for(auto j:divisor[a[i]]){
            if(j>1){
                ptr=min(ptr,st[j]);
                st[j]=min(st[j],i);
            }
        }
        if(ptr==n){
            base++;
            all_pos.emplace_back(i);
            for(auto j:divisor[a[i]]){
                pos[j].emplace_back(i);
            }
        }else{
            int res=all_pos.end()-upper_bound(all_pos.begin(),all_pos.end(),ptr);
            int res2=res;
            for(auto j:divisor[a[i]]){
                int cnt=pos[j].end()-upper_bound(pos[j].begin(),pos[j].end(),ptr);
                res-=cnt*mob[j];
                res2-=(int)pos[j].size()*mob[j];
            }
            diff=max(diff,res);
            diff=max(diff,res2-1);
        }
    }
    cout << base-diff << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    mob[1]=1;
    for(int i=1;i<N;i++){
        divisor[i].emplace_back(i);
        for(int j=i*2;j<N;j+=i){
            mob[j]-=mob[i];
            divisor[j].emplace_back(i);
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}