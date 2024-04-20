#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int n;
int a[N],idx[N],pre[N];
int last;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    vector<int> v;
    v.push_back(INT_MIN);
    int lis=0;
    for(int i=1;i<=n;i++){
        int val=lower_bound(v.begin(),v.end(),a[i])-v.begin();
        pre[i]=idx[val-1];
        if(val>lis){
            last=i;
            lis=val;
        }
        if(val<v.size()){
            v[val]=a[i];
        }else{
            v.push_back(a[i]);
        }
        idx[val]=i;
    }
    cout << lis << "\n";
    vector<int> ans;
    for(int i=last;i!=0;i=pre[i]){
        ans.push_back(a[i]);
    }
    reverse(ans.begin(),ans.end());
    for(auto x:ans)cout << x << " ";
}