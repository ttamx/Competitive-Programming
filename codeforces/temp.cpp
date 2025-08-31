#include<bits/stdc++.h>
#define int long long
using namespace std;
int curx,cury;
int cross(int x1,int y1,int x2,int y2){
    return x1*y2-x2*y1;
}
struct flam{
    int x,y;
    friend bool operator<(flam a,flam b){
        return (cross(a.x-curx,a.y-cury,b.x-curx,b.y-cury)>0);
    }
    flam(int _x=0,int _y=0){
        x=_x,y=_y;
    }
};
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m;cin>>n>>m;
    vector<flam>v;
    vector<int>xx;
    for(int i=1;i<=m;i++){
        int x,y;cin>>x>>y;
        v.push_back(flam(x,y));
        xx.push_back(x);
    }
    sort(xx.begin(),xx.end());
    int cur=0;
    curx=1;
    cury=0;
    int rans=0;
    sort(v.begin(),v.end());
    for(int i=1;i<=n;i++){
        int yes=0;
        while(cur<xx.size()){
            if(cur>=xx.size()){
                cout<<"bruh\n";
                return 0;
            }
            if(xx[cur]>i)break;
            cur++,yes=1;
        }
        cerr<<"cur:"<<cur<<" "<<xx[cur]<<"\n";
        if(yes){
            curx=i;
            cury=0;
            sort(v.begin(),v.end());
            cerr << "CC" << "\n";
        }
        sort(v.begin(),v.end());
        cerr<<"i:"<<i<<"\n";
        for(auto x:v)cerr<<x.x-curx<<" "<<x.y-cury<<"\n";
        cerr<<"\n";
        int prvx=-1;
        int prvy=-1;
        int cnt=0;
        int ans=0;
        for(auto x:v){
            if((prvx==-1)||(((prvx-i)*x.y)!=(prvy*(x.x-i)))){
                prvx=x.x;
                prvy=x.y;
                cnt=1;
            }else{
                cnt++;
            }
            ans=max(ans,cnt);
        }
        cout<<ans<<"\n";
        rans+=ans;
    }
    cout<<rans;
}