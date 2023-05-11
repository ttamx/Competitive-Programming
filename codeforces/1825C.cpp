#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<bool> b(m+1);
    int l=0,r=0;
    int cnt=0;
    int ans=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(x==-1){
            r++;
        }else if(x==-2){
            l++;
        }else{
            if(b[x])continue;
            b[x]=true;
            cnt++;
        }
    }
    auto sol1=[&](vector<bool> b,int cnt){
        int idx=1;
        for(int i=0;i<l;i++){
            while(b[idx])idx++;
            if(idx<=m){
                b[idx]=true;
                cnt++;
            }
        }
        ans=max(ans,cnt);
    };
    auto sol2=[&](vector<bool> b,int cnt){
        int idx=m;
        for(int i=0;i<r;i++){
            while(b[idx])idx--;
            if(idx>=1){
                b[idx]=true;
                cnt++;
            }
        }
        ans=max(ans,cnt);
    };
    sol1(b,cnt);
    sol2(b,cnt);
    int cl=0,cr=cnt;
    for(int i=1;i<=m;i++){
        if(!b[i])continue;
        cr--;
        int res=min(i-1-cl,r)+cnt+min(m-i-cr,l);
        ans=max(ans,res);
        cl++;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}