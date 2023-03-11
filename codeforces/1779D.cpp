#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    int m;
    cin >> m;
    priority_queue<int> r;
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        r.push(x);
    }
    map<int,vector<int>> mp;
    for(int i=0;i<n;i++){
        if(a[i]<b[i]){
            cout << "NO\n";
            return;
        }
        mp[b[i]].push_back(i);
    }
    set<int> s;
    s.insert(n);
    auto it=prev(mp.end());
    while(true){
        auto [x,v]=*it;
        vector<int> v2;
        for(auto y:v)if(a[y]>b[y])v2.push_back(y);
        if(!v2.empty()){
            int i=0,j=0;
            auto itt=s.upper_bound(v2[i]);
            while(j<v2.size()){
                while(!r.empty()&&r.top()!=x)r.pop();
                if(r.empty()){
                    cout << "NO\n";
                    return;
                }
                while(j<v2.size()&&v2[j]<*itt)j++;
                r.pop();
                if(j==v2.size())break;
                i=j;
                while(v2[i]>=*itt)itt=next(itt);
            }
        }
        for(auto y:v)s.insert(y);
        if(it==mp.begin())break;
        it=prev(it);
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}