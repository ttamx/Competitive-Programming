#include<bits/stdc++.h>

using namespace std;

const int N=505;

int red[N],blue[N];
int n,m,cut=1;
bool a=0;

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cin >> n >> m;    
    for(int i=1;i<=n;++i) cin >> red[i];
    for(int i=1;i<=m;++i) cin >> blue[i];
    if(red[1]>blue[1]) cut+=1;
    for(int i=1,j=1;i<=n;){
        if(blue[i]>red[i]&&blue[i]<red[i+1]){
            cut+=1;
            a=1;
            continue;
        }
        if(a==1){
            a=0;
            if(blue[i]==red[i]) cut+=1;
            if(blue[i]<red[i]&&blue[i+1]>red[i+1]&&red[i+1]!=0) cut+=2;
        }            

    }
}

