#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> l(n),r(n);
    for(int i=0;i<n;i++)cin >> l[i] >> r[i];
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return r[i]<r[j]||(r[i]==r[j]&&l[i]>l[j]);
    });
    stack<int> s;
    DSU dsu(n);
    for(auto i:ord)if(l[i]<r[i]){
        while(!s.empty()&&r[s.top()]>l[i]){
            int j=s.top();
            s.pop();
            dsu.merge(i,j);
        }
        s.emplace(i);
    }
    while(!s.empty())s.pop();
    queue<int> q;
    for(auto i:ord)if(l[i]==r[i])q.emplace(i);
    for(auto i:ord)if(r[i]-l[i]>1){
        while(!q.empty()&&r[q.front()]<r[i]){
            s.emplace(q.front());
            q.pop();
        }
        while(!s.empty()&&r[s.top()]>l[i]){
            int j=s.top();
            s.pop();
            dsu.merge(i,j);
        }
    }
    for(int i=0;i<n;i++)cout << dsu.size(i) << " \n"[i==n-1];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}