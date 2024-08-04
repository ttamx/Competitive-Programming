#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

const int N=2e6+5;

int n,d,t,ans;
int a[N],pre[N],dep[N],cnt[N];
stack<pair<int,int>> s;
stack<int> st;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> d >> t;
    for(int i=1;i<=n;i++)cin >> a[i];
    s.emplace(-INF,0);
    for(int i=1;i<=n;i++){
        int x=min(a[i],t)-i;
        while(s.top().first>x)s.pop();
        if(a[i]>t)pre[i]=s.top().second;
        else ans++;
        s.emplace(a[i]-i,i);
        if(pre[i]){
            ans++;
            int deep=0,j;
            while(!st.empty()&&pre[j=st.top()]>=pre[i]){
                st.pop();
                if(dep[j]>dep[deep])deep=j;
            }
            dep[i]=dep[deep]+1;
            cnt[dep[i]]++;
            cnt[dep[i]-1]--;
            st.emplace(i);
        }
    }
    for(int i=n;i>=1;i--)while(cnt[i]--&&d-->0)ans-=i;
    cout << ans;
}