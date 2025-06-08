#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int INF=INT_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    int mn=INF,mx=-INF;
    for(auto &[x,y]:a){
        cin >> x >> y;
        mn=min(mn,y);
        mx=max(mx,y);
    }
    sort(a.begin(),a.end());
    vector<pair<int,int>> ans;
    if(mn==mx){
        ans=a;
        if(mn>1){
            ans.emplace_back(a[0].first,mn-1);
        }else{
            ans.emplace_back(a[0].first,mn+1);
        }
    }else if(a[0].first==a[n-1].first){
        ans=a;
        if(a[0].first>1){
            ans.emplace_back(a[0].first-1,mn);
        }else{
            ans.emplace_back(a[0].first+1,mn);
        }
    }else{
        vector<pair<int,int>> base,b;
        int l=-1,r;
        for(auto [x,y]:a){
            if(l==-1)l=x;
            r=x;
            if(y==mn){
                base.emplace_back(x,y);
            }else{
                b.emplace_back(x,y);
            }
        }
        base.emplace_back(l,mn);
        base.emplace_back(r,mn);
        sort(base.begin(),base.end());
        base.erase(unique(base.begin(),base.end()),base.end());
        vector<pair<int,int>> c;
        while(!b.empty()&&b.back().first==r){
            c.emplace_back(b.back());
            b.pop_back();
        }
        ans=c;
        reverse(base.begin(),base.end());
        ans.insert(ans.end(),base.begin(),base.end());
        for(auto [x,y]:b){
            if(l!=x){
                if(l+1<x){
                    ans.emplace_back(l+1,mn+1);
                }
                if(y!=mn+1){
                    ans.emplace_back(x,mn+1);
                }
                l=x;
            }
            ans.emplace_back(x,y);
        }
        assert(l<r);
        if(l+1<r){
            ans.emplace_back(l+1,mn+1);
            l++;
        }
        if(l<r-1){
            ans.emplace_back(r-1,mn+1);
        }
    }
    assert(ans.size()<=3*n);
    cout << ans.size() << "\n";
    for(auto [x,y]:ans){
        cout << x << " " << y << "\n";
    }
}