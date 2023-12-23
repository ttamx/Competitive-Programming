#include<bits/stdc++.h>

using namespace std;

int n,m,q;
map<int,int> line;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=0;i<m;i++){
        int a,k;
        cin >> a >> k;
        line[a]++;
        line[a+k]--;
    }
    line[1];
    for(auto it=next(line.begin());it!=line.end();it++){
        it->second+=prev(it)->second;
    }
    for(auto it=next(line.begin());it!=line.end();){
        if(it->second%2==prev(it)->second%2){
            it=line.erase(it);
        }else{
            it++;
        }
    }
    line[n+1];
    while(q--){
        int x;
        cin >> x;
        auto it=line.upper_bound(x);
        int r=it->first-1;
        int l=prev(it)->first;
        cout << r-l+1 << "\n";
    }
}