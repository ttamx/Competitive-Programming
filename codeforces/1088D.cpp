#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    auto ask=[&](int c,int d){
        cout << "? " << c << " " << d << endl;
        int res;
        cin >> res;
        return res;
    };
    int va=0,vb=0;
    int cur=ask(0,0);
    for(int i=1<<29;i>0;i>>=1){
        if(cur==1){
            if(ask(va|i,vb|i)==-1){
                va|=i;
                cur=ask(va,vb);
            }else if(ask(va|i,vb)==-1){
                va|=i;
                vb|=i;
            }
        }else if(cur==-1){
            if(ask(va|i,vb|i)==1){
                vb|=i;
                cur=ask(va,vb);
            }else if(ask(va|i,vb)==-1){
                va|=i;
                vb|=i;
            }
        }else{
            if(ask(va|i,vb)==-1){
                va|=i;
                vb|=i;
            }
        }
    }
    cout << "! " << va << " " << vb << endl;
}