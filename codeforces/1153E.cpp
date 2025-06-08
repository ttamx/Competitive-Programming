#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for(int t=0;t<2;t++){
        auto ask=[&](int x1,int x2,int y1,int y2){
            if(t)swap(x1,y1),swap(x2,y2);
            assert(x1<=x2&&y1<=y2);
            cout << "? " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
            int res;
            cin >> res;
            return res;
        };
        int x1=n+1,x2=0;
        for(int i=1;i<n;i++){
            if(ask(1,i,1,n)%2){
                x1=min(x1,i);
                x2=max(x2,i+1);
            }
        }
        if(x1<x2){
            int y1,y2;
            {
                int l=1,r=n;
                while(l<r){
                    int m=(l+r)/2;
                    if(ask(1,x1,1,m)%2)r=m;
                    else l=m+1;
                }
                y1=l;
            }
            {
                int l=1,r=n;
                while(l<r){
                    int m=(l+r)/2;
                    if(ask(x2,n,1,m)%2)r=m;
                    else l=m+1;
                }
                y2=l;
            }
            if(t)swap(x1,y1),swap(x2,y2);
            cout << "! " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
            exit(0);
        }
    }
    assert(false);
}