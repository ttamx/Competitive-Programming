#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(m));
    vector<int> sum(n);
    int cnt=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> a[i][j];
            cnt+=a[i][j];
            sum[i]+=a[i][j];
        }
    }
    if(cnt%n){
        cout << -1 << '\n';
        return;
    }
    int mean=cnt/n;
    vector<tuple<int,int,int>> ans;
    for(int i=0;i<m;i++){
        vector<tuple<int,int,int>> res;
        for(int j=0;j<n;j++)res.push_back({sum[j],a[j][i],j});
        sort(res.begin(),res.end());
        int l=0,r=n-1;
        while(l<r && get<0>(res[l])<mean && get<0>(res[r])>mean){
            while(l<r && get<0>(res[l])<mean && get<0>(res[r])>mean && get<1>(res[l])!=0)l++;
            while(l<r && get<0>(res[l])<mean && get<0>(res[r])>mean && get<1>(res[r])!=1)r--;
            if(l<r && get<0>(res[l])<mean && get<0>(res[r])>mean){
                sum[get<2>(res[l])]++;
                sum[get<2>(res[r])]--;
                ans.push_back({get<2>(res[l])+1,get<2>(res[r])+1,i+1});
                l++,r--;
            }
        }
    }
    cout << ans.size() << '\n';
    for(auto [x,y,z]:ans)cout << x << ' ' << y << ' ' << z << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}