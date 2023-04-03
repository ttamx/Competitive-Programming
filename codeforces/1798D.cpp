#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    int mn=1e9,mx=-1e9;
    priority_queue<int> pos,neg;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        mn=min(mn,x);
        mx=max(mx,x);
        if(x>=0)pos.emplace(x);
        else neg.emplace(-x);
    }
    int lim=mx-mn;
    vector<int> ans;
    int cnt=0,cur=0;
    int hi=mx,lo=0;
    while(!pos.empty()||!neg.empty()){
        while(!pos.empty()&&cur+pos.top()<=mx){
            cur+=pos.top();
            ans.emplace_back(pos.top());
            pos.pop();
        }
        if(!neg.empty()){
            cur-=neg.top();
            ans.emplace_back(-neg.top());
            neg.pop();
        }
        lo=min(lo,cur);
    }
    if(hi-lo>=lim){
        cout << "No\n";
    }else{
        cout << "Yes\n";
        for(auto x:ans)cout << x << " ";
        cout << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}