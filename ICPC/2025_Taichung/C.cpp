#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;

int n,m,k;
int a[N];

inline bool check(ll mid){
    priority_queue<int,vector<int>,greater<int>> pq;
    for(int i=n-1;i>=m;i--){
        if(!pq.empty()&&(a[i]-pq.top())>=mid){
            pq.pop();
        }
        pq.emplace(a[i]);
    }
    vector<bool> ed(m);
    for(int i=m-1;i>=0;i--){
        if(!pq.empty()&&(a[i]-pq.top())>=mid){
            pq.pop();
            ed[i]=true;
        }
    }
    if(!pq.empty())return false;
    int len=0;
    int cnt=0;
    priority_queue<ll> pq2;
    for(int i=0;i<m;i++){
        if(!pq2.empty()&&(pq2.top()-a[i])>=mid){
            pq2.pop();
        }else{
            cnt++;
            if(cnt==2){
                len+=a[0]+a[i];
            }else if(cnt>2){
                len+=a[i]*2;
            }
            if((cnt-1)*mid>(k-len))return false;
        }
        if(!ed[i]){
            pq2.emplace(a[i]);
        }
    }
    return true;
}

inline pair<ll,int> work(ll mid){
    priority_queue<int,vector<int>,greater<int>> pq;
    for(int i=n-1;i>=m;i--){
        if(!pq.empty()&&(a[i]-pq.top())>mid){
            pq.pop();
        }
        pq.emplace(a[i]);
    }
    vector<bool> ed(m);
    for(int i=m-1;i>=0;i--){
        if(!pq.empty()&&(a[i]-pq.top())>mid){
            pq.pop();
            ed[i]=true;
        }
    }
    if(!pq.empty())return {0,1};
    int len=0;
    int cnt=0;
    priority_queue<ll> pq2;
    for(int i=0;i<m;i++){
        if(!pq2.empty()&&(pq2.top()-a[i])>mid){
            pq2.pop();
        }else{
            cnt++;
            if(cnt==2){
                len+=a[0]+a[i];
            }else if(cnt>2){
                len+=a[i]*2;
            }
            if((cnt-1)*mid>(k-len))return {0,1};
        }
        if(!ed[i]){
            pq2.emplace(a[i]);
        }
    }
    return {(k-len)-(cnt-1)*mid,cnt-1};
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> k >> n >> m;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    ll ans=0;
    ll l=0,r=k;
    while(l<r){
        ll mid=(l+r+1)/2;
        if(check(mid))l=mid;
        else r=mid-1;
    }
    ans=l;
    auto [den,num]=work(ans);
    ll g=gcd(den,num);
    den/=g;
    num/=g;
    den+=num*ans;
    if(num==1){
        cout << den << "\n";
    }else{
        cout << den << "/" << num << "\n";
    }
}