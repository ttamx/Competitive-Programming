#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n,m;
        cin >> n >> m;
        if(m==0){
            cout << 0 << " " << 0 << "\n";
            continue;
        }
        int l=1,r=m;
        while(l<r){
            int mid=(l+r)/2;
            int t=m/mid;
            int cur=(mid+1)*t;
            int left=m-mid*t;
            if(left>0){
                cur+=left;
            }else{
                cur--;
            }
            if(cur<=n)r=mid;
            else l=mid+1;
        }
        cout << m << " " << l << "\n";
    }
}