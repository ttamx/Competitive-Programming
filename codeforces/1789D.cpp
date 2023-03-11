#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    string a,b;
    cin >> a >> b;
    string oa=a;
    if(a==b)return void(cout << "0\n");
    if(b==string(n,'0')||a==string(n,'0'))return void(cout << "-1\n");
    vector<int> ans;
    for(int i=0;i<n;i++){
        int one=0;
        while(a[one]=='0')one++;
        int idx=0;
        while(idx<n&&a[idx]==b[idx])idx++;
        if(idx==n)break;
        int k=one-idx;
        if(k==0)break;
        ans.emplace_back(k);
        string tmp=a;
        for(int i=0;i<n;i++){
            if(i+k>=0&&i+k<n){
                a[i]=((a[i]-'0')^(tmp[i+k]-'0'))+'0';
            }
        }
    }
    if(a==b){
        cout << ans.size() << '\n';
        for(auto x:ans)cout << x << ' ';
        cout << '\n';
        return;
    }
    a=oa;
    ans.clear();
    for(int i=0;i<n;i++){
        int one=n-1;
        while(a[one]=='0')one--;
        int idx=n-1;
        while(idx>=0&&a[idx]==b[idx])idx--;
        if(idx==n)break;
        int k=one-idx;
        if(k==0)break;
        ans.emplace_back(k);
        string tmp=a;
        for(int i=0;i<n;i++){
            if(i+k>=0&&i+k<n){
                a[i]=((a[i]-'0')^(tmp[i+k]-'0'))+'0';
            }
        }
    }
    if(a==b){
        cout << ans.size() << '\n';
        for(auto x:ans)cout << x << ' ';
        cout << '\n';
        return;
    }else{
        cout << -1 << '\n';
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}