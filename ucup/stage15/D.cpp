#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=998244353;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        int n=s.size();
        int ans=0;
        for(int i=0;i<n;i++)if(s[i]!='1'){
            int j=i;
            while(j+1<n&&s[j+1]!='1')j++;
            vector<int> a{0};
            for(int k=i;k<=j;k++){
                if(s[k]=='0'){
                    a.back()++;
                }else{
                    a.emplace_back(0);
                }
            }
            for(int k=0;k<a.size();k++){
                array<int,4> b{};
                if(k-2>=0)b[0]=a[k-2]+1;
                if(k-1>=0)b[1]=a[k-1]+1;
                if(k+1<a.size())b[2]=a[k+1]+1;
                if(k+2<a.size())b[3]=a[k+2]+1;
                ans=max(ans,a[k]+b[1]+min(b[0],b[2]));
                ans=max(ans,a[k]+b[2]+min(b[1],b[3]));
            }
            for(int k=1;k+2<a.size();k++){
                array<int,4> b{};
                if(k-3>=0)b[0]=a[k-3]+1;
                if(k-2>=0)b[1]=a[k-2]+1;
                if(k+3<a.size())b[2]=a[k+3]+1;
                if(k+4<a.size())b[3]=a[k+4]+1;
                int c=a[k]+a[k+1]+1;
                int l=max(c+a[k-1]+1,a[k-1]+b[1]+min(b[0],c+1));
                int r=max(c+a[k+2]+1,a[k+2]+b[2]+min(b[3],c+1));
                ans=max(ans,min(l,r));
            }
            i=j;
        }
        cout << ans << "\n";
    }
}