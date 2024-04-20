#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;

int n;
int a[N],pre[N];
ll cnt[N],sum;
stack<int> s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[n+i]=a[i];
        sum+=a[i];
    }
    for(int i=2*n;i>=1;i--){
        while(!s.empty()&&a[s.top()]>=a[i]){
            int j=s.top();
            s.pop();
            if(i<=n){
                ll val=a[j]-a[pre[j]];
                cnt[pre[j]-j]+=val;
                cnt[pre[j]-i]-=val;
            }
        }
        if(!s.empty())pre[i]=s.top();
        else pre[i]=i;
        s.emplace(i);
    }
    for(int i=1;i<=n;i++){
        cnt[i]+=cnt[i-1];
        sum-=cnt[i];
        cout << sum << "\n";
    }
}