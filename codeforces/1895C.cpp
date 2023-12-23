#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<string> vec[7];
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        vec[s.size()].emplace_back(s);
    }
    long long ans=0;
    for(int i=1;i<=5;i++){
        for(int j=1;j<=5;j++){
            if((i+j)%2)continue;
            int m=(i+j)/2;
            map<int,int> mp1,mp2;
            for(auto s:vec[i]){
                int sum=0;
                for(int k=0;k<i;k++)sum+=(s[k]-48)*(k<m?1:-1);
                mp1[sum]++;
            }
            for(auto s:vec[j]){
                int sum=0;
                for(int k=0;k<j;k++)sum+=(s[k]-48)*(k+i<m?-1:1);
                mp2[sum]++;
            }
            for(auto [x,y]:mp1)ans+=1ll*y*mp2[x];
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}