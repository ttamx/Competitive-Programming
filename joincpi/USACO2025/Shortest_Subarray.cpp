#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    vector<bool> f(n);
    vector<int> b;
    for(auto x:a){
        if(!f[x]){
            b.emplace_back(x);
            f[x]=true;
        }
    }
    int m=b.size();
    vector<int> id(n);
    for(int i=0;i<m;i++){
        id[b[i]]=i;
    }
    int ans=n;
    vector<int> dp(m,-INF);
    deque<pair<int,int>> dq;
    for(int i=0;i<n;i++){
        int j=id[a[i]];
        if(j==0){
            while(!dq.empty()&&dq.back().first==0){
                dq.pop_back();
            }
            dq.emplace_back(0,i);
        }else{
            while(!dq.empty()&&dq.back().first<j-1){
                dq.pop_back();
            }
            if(!dq.empty()&&dq.back().first==j-1){
                dq.back().first++;
                auto tmp=dq.back();
                dq.pop_back();
                while(!dq.empty()&&dq.back().first<=tmp.first){
                    dq.pop_back();
                }
                dq.emplace_back(tmp);
            }
        }
        if(!dq.empty()&&dq.back().first==m-1){
            ans=min(ans,i-dq.back().second+1);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}