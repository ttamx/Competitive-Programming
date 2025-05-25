#include<bits/stdc++.h>

using namespace std;

const int N=405;

int n,m;
int a[N],l[N],r[N],cnt[N];
int ans[N];

int calc(vector<int> cand){
    int res=0,last=0;
    sort(cand.begin(),cand.end(),[&](int i,int j){
        return r[i]<r[j]||(r[i]==r[j]&&l[i]<l[j]);
    });
    for(auto i:cand){
        if(l[i]>last){
            last=r[i];
            res++;
        }
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        cnt[a[i]]++;
    }
    for(int i=1;i<=m;i++){
        cin >> l[i] >> r[i];
    }
    for(int i=n;i>=1;i--){
        if(cnt[i]==0)continue;
        vector<int> cand;
        for(int j=1;j<=m;j++){
            if(ans[j])continue;
            cand.emplace_back(j);
            if(calc(cand)>cnt[i]){
                cand.pop_back();
            }
        }
        for(auto j:cand){
            ans[j]=i;
        }
    }
    for(int i=1;i<=m;i++){
        cout << ans[i] << "\n";
    }
}