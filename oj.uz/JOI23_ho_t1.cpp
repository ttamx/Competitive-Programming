#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n;
int a[N],ans[N];
map<int,vector<int>> mp;
stack<int> s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    s.emplace(0);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        auto &p=mp[a[i]];
        if(!p.empty()){
            while(s.top()>p.back()){
                mp[a[s.top()]].pop_back();
                s.pop();
            }
        }
        s.emplace(i);
        p.emplace_back(i);
    }
    for(int i=n,col;i>=1;i--){
        if(s.top()==i){
            col=a[s.top()];
            s.pop();
        }
        ans[i]=col;
    }
    for(int i=1;i<=n;i++)cout << ans[i] << "\n";
}