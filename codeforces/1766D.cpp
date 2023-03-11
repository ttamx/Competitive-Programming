#include<bits/stdc++.h>

using namespace std;

const int N=3200;

bool b[N];
vector<int> p;

void runcase(){
    long long a,b;
    cin >> a >> b;
    long long x=b-a;
    if(x==1){
        cout << -1 << '\n';
        return;
    }
    long long ans=1e18;
    for(int i=0;i<p.size();i++){
        if(x%p[i])continue;
        long long na=((a-1)/p[i]+1)*p[i]-a;
        long long nb=((b-1)/p[i]+1)*p[i]-b;
        ans=min({ans,na,nb});
        while(x%p[i]==0)x/=p[i];
    }
    if(x>1){
        long long na=((a-1)/x+1)*x-a;
        long long nb=((b-1)/x+1)*x-b;
        ans=min({ans,na,nb});
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(b[i])continue;
        p.push_back(i);
        for(int j=i;j<N;j+=i)b[j]=true;
    }
    int t;
    cin >> t;
    while(t--)runcase();
}