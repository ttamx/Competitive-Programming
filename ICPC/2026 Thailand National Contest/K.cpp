#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string a,b;
        cin >> a >> b;
        int ans=0;
        for(int t=0;t<2;t++){
            for(int i=0;i<n;i++)if(a[i]=='.'){
                int j=i;
                while(j+1<n&&a[j+1]=='.')j++;
                int res=0,cur=0;
                for(int k=i;k<=j;k++){
                    if(b[k]=='.')res=max(res,++cur);
                    else cur=0;
                }
                ans=max(ans,res+j-i+1);
                i=j;
            }
            swap(a,b);
        }
        cout << ans << "\n";
    }
}