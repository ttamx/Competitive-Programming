#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = complex<ll>;

ll dot(P a,P b){return real(conj(a)*b);}
ll cross(P a,P b){return imag(conj(a)*b);}

int side(P a){return imag(a)>0||(imag(a)==0&&real(a)>0);}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<P> a(n);
    for(auto &p:a){
        ll x,y;
        cin >> x >> y;
        p=P(x,y);
    }
    vector<ll> ans(n+2);
    for(int s=0;s<n;s++){
        vector<P> b;
        for(int i=0;i<n;i++)if(i!=s)b.emplace_back(a[i]-a[s]);
        sort(b.begin(),b.end(),[&](P x,P y){
            int u=side(x),v=side(y);
            if(u!=v)return u>v;
            return cross(u,v)>0;
        });
        for(auto p:b){
            cerr << p << " ";
        }
        cerr << "\n";
        b.insert(b.end(),b.begin(),b.end());
        int l=0,r=0;
        for(int i=0;i<n-1;i++){
            l=max(l,i+1);
            r=max(r,i+1);
            while(r<i+n-1&&cross(b[i],b[r])>0)r++;
            while(l<r&&dot(b[i],b[l])>0)l++;
            ans[l-i]++;
            ans[r-i]--;
        }
        reverse(b.begin(),b.end());
        l=0,r=0;
        for(int i=0;i<n-1;i++){
            l=max(l,i+1);
            r=max(r,i+1);
            while(r<i+n-1&&cross(b[i],b[r])<0)r++;
            while(l<r&&dot(b[i],b[l])>0)l++;
            ans[l-i]++;
            ans[r-i]--;
        }
    }
    for(int i=1;i<=n;i++)ans[i]+=ans[i-1];
    for(int i=1;i<=n-2;i++){
        cout << ans[i] << "\n";
    }
}