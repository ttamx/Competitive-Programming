#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=400005;
const int OFFSET=100000;

struct Fenwick{
    ll t[N];
    void update(int i,ll v){
        for(i+=OFFSET;i<N;i+=i&-i){
            t[i]+=v;
        }
    }
    ll query(int i){
        ll res=0;
        for(i+=OFFSET;i>0;i-=i&-i){
            res+=t[i];
        }
        return res;
    }
}f;

vector<ll> mosaic(vector<int> X,vector<int> Y,vector<int> T,vector<int> B,vector<int> L,vector<int> R){
    int n=X.size();
    int q=T.size();
    vector<ll> ans(q);
    if(n<=5000){
        vector<vector<int>> a(n,vector<int>(n));
        a[0]=X;
        for(int i=1;i<n;i++)a[i][0]=Y[i];
        for(int i=1;i<n;i++){
            for(int j=1;j<n;j++){
                if(a[i-1][j]+a[i][j-1]==0){
                    a[i][j]=1;
                }
            }
        }
        auto b=a;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i>0){
                    b[i][j]+=b[i-1][j];
                }
                if(j>0){
                    b[i][j]+=b[i][j-1];
                }
                if(i>0&&j>0){
                    b[i][j]-=b[i-1][j-1];
                }
            }
        }
        for(int i=0;i<q;i++){
            ans[i]=b[B[i]][R[i]];
            if(T[i]>0){
                ans[i]-=b[T[i]-1][R[i]];
            }
            if(L[i]>0){
                ans[i]-=b[B[i]][L[i]-1];
            }
            if(T[i]>0&&L[i]>0){
                ans[i]+=b[T[i]-1][L[i]-1];
            }
        }
        return ans;
    }
    vector<int> a(n),b(n),c(n),d(n);
    a[0]=Y[1];
    b[0]=X[1];
    for(int i=1;i<n;i++){
        if(a[i-1]+X[i]==0){
            a[i]=1;
        }
    }
    for(int i=1;i<n;i++){
        if(b[i-1]+Y[i]==0){
            b[i]=1;
        }
    }
    c[1]=b[2];
    d[1]=a[2];
    vector<ll> s;
    for(int i=2;i<n;i++){
        if(c[i-1]+a[i]==0){
            c[i]=1;
            s.emplace_back(2-i);
        }
    }
    for(int i=2;i<n;i++){
        if(d[i-1]+b[i]==0){
            d[i]=1;
            if(i>2){
                s.emplace_back(i-2);
            }
        }
    }
    sort(s.begin(),s.end());
    auto qs=s;
    for(int i=1;i<qs.size();i++){
        qs[i]+=qs[i-1];
    }
    for(int i=1;i<n;i++){
        X[i]+=X[i-1];
        Y[i]+=Y[i-1];
        a[i]+=a[i-1];
        b[i]+=b[i-1];
    }
    for(int i=0;i<q;i++){
        if(T[i]==0){
            ans[i]+=X[R[i]]-(L[i]>0?X[L[i]-1]:0);
            T[i]++;
        }
    }
    for(int i=0;i<q;i++){
        if(T[i]<=B[i]&&L[i]==0){
            ans[i]+=Y[B[i]]-Y[T[i]-1];
            L[i]++;
        }
    }
    for(int i=0;i<q;i++){
        if(T[i]<=B[i]&&L[i]<=R[i]&&T[i]==1){
            ans[i]+=a[R[i]]-a[L[i]-1];
            T[i]++;
        }
    }
    for(int i=0;i<q;i++){
        if(T[i]<=B[i]&&L[i]<=R[i]&&L[i]==1){
            ans[i]+=b[B[i]]-b[T[i]-1];
            L[i]++;
        }
    }
    for(int i=0;i<q;i++){
        if(T[i]>B[i]||L[i]>R[i]){
            continue;
        }
        {
            auto itl=lower_bound(s.begin(),s.end(),T[i]-R[i]);
            auto itr=upper_bound(s.begin(),s.end(),T[i]-L[i]);
            if(itl!=itr){
                auto it=lower_bound(itl,itr,B[i]-R[i]);
                int l=itl-s.begin();
                int r=itr-s.begin();
                int p=it-s.begin();
                ans[i]+=((p>0?qs[p-1]:0LL)-(l>0?qs[l-1]:0LL))+1LL*(R[i]-T[i])*(p-l);
                ans[i]+=1LL*(B[i]-T[i])*(r-p);
                ans[i]+=r-l;
            }
        }
        if(T[i]!=B[i]){
            auto itl=lower_bound(s.begin(),s.end(),T[i]-L[i]+1);
            auto itr=upper_bound(s.begin(),s.end(),B[i]-L[i]);
            if(itl!=itr){
                auto it=lower_bound(itl,itr,B[i]-R[i]);
                int l=itl-s.begin();
                int r=itr-s.begin();
                int p=it-s.begin();
                ans[i]+=-((r>0?qs[r-1]:0LL)-(p>0?qs[p-1]:0LL))+1LL*(B[i]-L[i])*(r-p);
                ans[i]+=1LL*(R[i]-L[i])*(p-l);
                ans[i]+=r-l;
            }
        }
    }
    return ans;
}
