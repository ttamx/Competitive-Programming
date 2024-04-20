#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int N=1e6+5;

struct Rec{
    ll h,w;
    Rec(ll _h,ll _w):h(_h),w(_w){}
    ll area(){
        return h*w;
    }
};

int n;
string a;
ll sum,ans,cnt;
stack<Rec> s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> a;
    a=" "+a;
    for(int i=1;i<=n;i++){
        if(a[i]=='F'){
            ans+=sum;
            s.push(Rec(0,1));
        }else{
            cnt++;
            Rec res(cnt,0);
            while(!s.empty()&&s.top().h<res.h){
                auto tmp=s.top();
                s.pop();
                sum-=tmp.area();
                res.w+=tmp.w;
            }
            if(res.w>0){
                s.push(res);
                sum+=res.area();
            }
            ans+=sum+cnt*(cnt+1)/2;
            if(i==n||a[i+1]=='F'){
                for(int j=cnt;j>0;j--){
                    Rec res(j,1);
                    s.push(res);
                    sum+=res.area();
                }
                cnt=0;
            }
        }
    }
    cout << ans;
}