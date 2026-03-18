#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=20;

string a[N];

ll calc(ll h,ll w){
    return ((h*(h-1)/2)*(w*(w-1)/2));
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll k;
    cin >> k;
    for(int i=0;i<N;i++){
        a[i]=string(N,'.');
    }
    int oh=0,ow=0;
    while(k>0){
        int h=1,w=1;
        if(oh<=ow){
            while(calc(h,N-ow)<k)h++;
            while(calc(h,w+1)<=k)w++;
            k-=calc(h,w);
            assert(oh+h<=N);
            assert(ow+w<=N);
            for(int i=0;i<h;i++){
                for(int j=0;j<w;j++){
                    a[oh+i][ow+j]='#';
                }
            }
            oh+=h+1;
        }else{
            while(calc(N-ow,w)<k)w++;
            while(calc(h+1,w)<=k)h++;
            k-=calc(h,w);
            assert(oh+h<=N);
            assert(ow+w<=N);
            for(int i=0;i<h;i++){
                for(int j=0;j<w;j++){
                    a[oh+i][ow+j]='#';
                }
            }
            ow+=w+1;
        }
    }
    assert(k==0);
    cout << N << " " << N << "\n";
    for(int i=0;i<N;i++){
        cout << a[i] << "\n";
    }
}