#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,x;
    cin >> n >> x;
    vector<bool> b(n+1,false);
    vector<int> ans;
    b[x]=true;
    b[1]=true;
    ans.push_back(x);
    for(int i=2;i<n;i++){
        if(!b[i])ans.push_back(i);
        else{
            for(int j=i;j<=n;j+=i){
                if(b[j])continue;
                if(n%j!=0)continue;
                b[j]=true;
                ans.push_back(j);
                break;
            }
            if(ans.size()<i){
                cout << -1 << '\n';
                return;
            }
        }
    }
    ans.push_back(1);
    for(auto i:ans)cout << i << ' ';
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}