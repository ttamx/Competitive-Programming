#include<bits/stdc++.h>

using namespace std;

int n;

void add(int x){
    if(x<=2||x>=2*n)return;
    cout << "+ " << x << endl;
}

int ask(int i,int j){
    cout << "? " << i << " " << j << endl;
    int res;
    cin >> res;
    return res;
}

void runcase(){
    cin >> n;
    int m=(n+1)/2;
    add(m*2);
    vector<int> ans(n);
    if(n%2==1){
        vector<int> vec;
        for(int i=2;i<n;i++)if(ask(1,i)==-1)vec.emplace_back(i);
        if(vec.empty()){
            vec.emplace_back(n);
        }
        if(vec.size()>1){
            vec.clear();
            vec.emplace_back(1);
        }
        add(m*2-1);
        int st=vec[0];
        ans[st-1]=m;
        for(int i=1;i<=n;i++){
            if(i==st)continue;
            int res=ask(st,i);
            if(res%2==1){
                ans[i-1]=m-(res+1)/2;
            }else{
                ans[i-1]=m+res/2;
            }
        }
    }else{
        add(m*2-1);
        vector<int> vec;
        for(int i=2;i<n;i++)if(ask(1,i)==-1)vec.emplace_back(i);
        if(vec.empty()){
            vec.emplace_back(n);
        }
        if(vec.size()>1){
            vec.clear();
            vec.emplace_back(1);
        }
        add(2*n-1);
        int st=vec[0];
        ans[st-1]=n;
        for(int i=1;i<=n;i++){
            if(i==st)continue;
            int res=ask(st,i);
            if(res%2==1){
                ans[i-1]=n-(res+1)/2;
            }else{
                ans[i-1]=res/2;
            }
        }
    }
    cout << "!";
    for(auto x:ans)cout << ' ' << x;
    reverse(ans.begin(),ans.end());
    for(auto x:ans)cout << ' ' << x;
    cout << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}