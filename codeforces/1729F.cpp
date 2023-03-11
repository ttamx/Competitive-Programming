#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int t;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> t;
    while(t--){
        int qs[N],a[N];
        string str;
        cin >> str;
        int n=str.size();
        str=" "+str;
        for(int i=1;i<=n;++i){
            qs[i]=(qs[i-1]+str[i]-'0')%9;
        }
        int w,m;
        cin >> w >> m;
        vector<int> r[10];
        for(int i=1;i+w-1<=n;++i){
            a[i]=(9+qs[i+w-1]-qs[i-1])%9;
            r[a[i]].emplace_back(i);
        }
        while(m--){
            int x,y,k;
            cin >> x >> y >> k;
            int v=(9+qs[y]-qs[x-1])%9;
            pair<int,int> ans={2e9,2e9};
            for(int i=0;i<9;++i){
                if(r[i].size()==0)continue;
                int val=(9+k-((v*i)%9))%9;
                if(r[val].size()==0)continue;
                if(i==val){
                    if(r[i].size()<=1)continue;
                    ans=min(ans,{r[i][0],r[i][1]});
                }else{
                    ans=min(ans,{r[i][0],r[val][0]});
                }
            }
            if(ans.first==2e9)ans={-1,-1};
            cout << ans.first << " " << ans.second << "\n";
        }
    }
}

