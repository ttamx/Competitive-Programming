#include<bits/stdc++.h>

using namespace std;
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    for(auto &[l,r]:a)cin >> l >> r;
    vector<int> ans1(n,-1),ans2(n,-1);
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return a[i]<a[j];
    });
    bool f=false;
    int p=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    priority_queue<tuple<int,int,int>> pq2;
    for(int i=1;i<=n;i++){
        while(p<n&&a[ord[p]].first<=i){
            pq.emplace(a[ord[p]].second,ord[p]);
            p++;
        }
        assert(!pq.empty());
        auto [r,j]=pq.top();
        assert(r>=i);
        pq.pop();
        ans1[j]=ans2[j]=i;
        if(!f){
            int l=a[j].first;
            while(!pq2.empty()&&get<2>(pq2.top())<i){
                pq2.pop();
            }
            if(!pq2.empty()&&l<=get<0>(pq2.top())){
                swap(ans2[get<1>(pq2.top())],ans2[j]);
                f=true;
            }
        }
        pq2.emplace(i,j,r);
    }
    if(!f){
        cout << "YES\n";
        for(auto x:ans1){
            cout << x << " ";
        }
        cout << "\n";
    }else{
        cout << "NO\n";
        for(auto x:ans1){
            cout << x << " ";
        }
        cout << "\n";
        for(auto x:ans2){
            cout << x << " ";
        }
        cout << "\n";
    }
}