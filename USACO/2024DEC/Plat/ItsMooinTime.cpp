#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=3e5+5;

int k,n;
string s;
ll a[N];

void update(vector<ll> &a,const vector<ll> &b){
    for(int i=0;i<b.size();i++){
        if(a.size()==i){
            a.emplace_back(b[i]);
        }else{
            a[i]=min(a[i],b[i]);
        }
    }
}

vector<ll> merge(const vector<ll> &a,const vector<ll> &b,bool add=false){
    assert(!a.empty()&&!b.empty());
    vector<ll> c{a[0]+b[0]};
    for(int i=1,j=1;i<a.size()||j<b.size();){
        if(j==b.size()||(i<a.size()&&a[i]-a[i-1]<b[j]-b[j-1])){
            c.emplace_back(a[i]-a[i-1]);
            i++;
        }else{
            c.emplace_back(b[j]-b[j-1]);
            j++;
        }
    }
    for(int i=1;i<c.size();i++){
        c[i]+=c[i-1];
    }
    if(add)c.insert(c.begin(),1e18);
    return c;
}

vector<vector<vector<ll>>> dnc(int l,int r){
    vector<vector<vector<ll>>> res(k+1,vector<vector<ll>>(k+1));
    if(l==r){
        if(s[l]=='M'){
            res[0][0]={0};
            res[k][k]={a[l]};
        }else{
            res[0][0]={a[l]};
            res[k][k]={0};
        }
        // cerr << "=== " << l << " " << r << " ===\n";
        // cerr << s.substr(l,r-l+1) << "\n";
        // cerr << "a : ";
        // for(int i=l;i<=r;i++){
        //     cerr << a[i] << " ";
        // }
        // cerr << "\n";
        // for(int i=0;i<=k;i++){
        //     for(int j=0;j<=k;j++){
        //         cerr << i << " " << j << " : ";
        //         for(auto x:res[i][j]){
        //             cerr << x << " ";
        //         }
        //         cerr << "\n";
        //     }
        // }
        return res;
    }
    int m=(l+r)/2;
    auto vl=dnc(l,m);
    auto vr=dnc(m+1,r);
    int sl=m-l+1,sr=r-m;
    for(int i=0;i<=k;i++){
        for(int j=0;j<=k;j++){
            if(vl[i][j].empty())continue;
            for(int x=0;x<=k;x++){
                for(int y=0;y<=k;y++){
                    if(vr[x][y].empty())continue;
                    if(i==k&&x==k){
                        update(res[k][k],merge(vl[i][j],vr[x][y]));
                    }else if(i==k){
                        update(res[min(sl+x,k-1)][y],merge(vl[i][j],vr[x][y]));
                    }else if(x==k){
                        update(res[i][min(j+sr,k-1)],merge(vl[i][j],vr[x][y]));
                    }else{
                        update(res[i][y],merge(vl[i][j],vr[x][y],j+x>=k-1));
                    }
                }
            }
        }
    }
    for(auto &v:res){
        for(auto &vv:v){
            for(auto &x:vv){
                x=min(x,(ll)1e18);
            }
        }
    }
    // for(int i=0;i<k;i++){
    //     for(int j=0;j<k;j++){
    //         if(i+1<k)update(res[i][j],res[i+1][j]);
    //         if(j+1<k)update(res[i][j],res[i][j+1]);
    //     }
    // }
    // cerr << "=== " << l << " " << r << " ===\n";
    // cerr << s.substr(l,r-l+1) << "\n";
    // cerr << "a : ";
    // for(int i=l;i<=r;i++){
    //     cerr << a[i] << " ";
    // }
    // cerr << "\n";
    // for(int i=0;i<=k;i++){
    //     for(int j=0;j<=k;j++){
    //         cerr << i << " " << j << " : ";
    //         for(auto x:res[i][j]){
    //             cerr << x << " ";
    //         }
    //         cerr << "\n";
    //     }
    // }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> k >> n;
    cin >> s;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    if(k==1){
        for(int i=0;i<n;i++){
            if(s[i]=='M'){
                a[i]=0LL;
            }
        }
        sort(a,a+n);
        ll ans=0;
        for(int i=0;i<n;i++){
            ans+=a[i];
            cout << ans << "\n";
        }
        exit(0);
    }
    s.push_back('M');
    a[n]=1e18;
    auto res=dnc(0,n);
    vector<ll> ans;
    for(auto &v:res){
        for(auto &x:v){
            update(ans,x);
        }
    }
    for(int i=n/k-1;i>=1;i--){
        ans[i]=min(ans[i],ans[i+1]);
    }
    for(int i=1;i<=n/k;i++){
        cout << ans[i] << "\n";
    }
}