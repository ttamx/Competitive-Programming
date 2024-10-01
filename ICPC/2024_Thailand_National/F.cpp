#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    bool swapp=false;
    if(n>m){
        swapp=true;
        swap(n,m);
    }
    if(n<3){
        cout << -1 << "\n";
        return;
    }
    vector<tuple<int,int,int,int,int,int>> ans;
    if(n==3){
        if(m<6){
            cout << -1 << "\n";
            return;
        }
        ans.emplace_back(2,1,1,0,1,1);
        ans.emplace_back(3,3,1,1,0,m-4);
        ans.emplace_back(1,4,0,2,1,m-5);
        ans.emplace_back(2,m,1,m-5,1,0);
    }else{
        int offset=0;
        while(n>5){
            ans.emplace_back(n-1,offset+1,n-2,0,1,1);
            ans.emplace_back(n-1,offset+m,n-2,m-4,1,0);
            ans.emplace_back(n,offset+3,1,1,0,m-4);
            n-=2,m-=2;
            offset++;
        }
        if(n==4){
            ans.emplace_back(2,1+offset,1,0,1,m-3);
            ans.emplace_back(3,m+offset,1,m-3,1,0);
            ans.emplace_back(4,2+offset,1,1,0,m-3);
            ans.emplace_back(1,m-1+offset,0,m-3,1,1);
        }else{
            ans.emplace_back(2,1+offset,1,0,2,m-3);
            ans.emplace_back(5,2+offset,1,1,0,m-3);
            ans.emplace_back(3,3+offset,0,1,1,m-4);
            ans.emplace_back(1,m-1+offset,0,m-3,1,1);
            ans.emplace_back(4,m+offset,2,m-4,1,0);
        }
    }
    for(auto &[x,y,u,l,d,r]:ans)swap(x,y);
    cout << ans.size() << "\n";
    for(auto [x,y,u,l,d,r]:ans){
        if(swapp){
            swap(x,y);
            swap(u,l);
            swap(d,r);
        }
        cout << x << " " << y << " " << u << " " << l << " " << d << " " << r << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}