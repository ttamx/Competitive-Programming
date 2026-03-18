#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int p,q,r;
    cin >> p >> q >> r;
    int n=p+1;
    int d1=q-n+4;
    int d3=q-n+2;
    int d2=n-d1-d3;
    if(d2<0||d3<0){
        cout << "-1\n";
        return;
    }
    if(d3==0){
        if(q==n-2&&r==max(0,n-3)){
            cout << n << "\n";
            for(int i=2;i<=n;i++){
                cout << i-1 << " " << i << "\n";
            }
        }else{
            cout << "-1\n";
        }
        return;
    }
    int base=4*(d3-1);
    vector<int> a(d3-1),b(d1);
    r-=base;
    if(r<0){
        cout << "-1\n";
        return;
    }
    if(d2>0){
        if(d3>1&&r<=d2-1&&d2-r>0&&d2-r<=d3-1){
            for(int i=0;i<d2-r;i++){
                a[i]++;
            }
            a[0]+=r;
        }else{
            bool ok=false;
            for(int i=1;i<=min(d1,d2);i++){
                int cur=r-2*i;
                if(cur<0)break;
                int left=d2-i;
                int ext=left-cur;
                if(ext>=0&&ext<=d3-1){
                    for(int j=0;j<ext;j++){
                        a[j]++;
                    }
                    for(int j=0;j<i;j++){
                        b[j]++;
                    }
                    b[0]+=cur;
                    ok=true;
                    break;
                }
            }
            if(!ok){
                cout << "-1\n";
                return;
            }
        }
    }else if(r!=0){
        cout << "-1\n";
        return;
    }
    int cur=d1+d3;
    auto build=[&](int u,int v,int c){
        for(int i=0;i<c;i++){
            cout << u << " " << ++cur << "\n";
            u=cur;
        }
        cout << u << " " << v << "\n";
    };
    cout << n << "\n";
    for(int i=2;i<=d3;i++){
        build(i-1,i,a[i-2]);
    }
    for(int i=1;i<=d3;i++){
        build(i,d3+i,b[i]);
    }
    build(1,d1+d3-1,b[0]);
    build(d3,d1+d3,b[d1-1]);
    assert(cur==n);
}


int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}