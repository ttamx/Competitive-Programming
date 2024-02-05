#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    set<int> ans;
    for(int i=1;i<n;i++)if(a[i]==a[i-1])ans.emplace(a[i]);
    for(int i=2;i<n;i++)if(a[i]==a[i-2])ans.emplace(a[i]);
    for(auto it=ans.begin();it!=ans.end();)cout << *it << " \n"[++it==ans.end()];
    if(ans.empty())cout << "-1\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}