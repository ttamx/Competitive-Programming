#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    int sum=0;
    for(auto &x:a)cin >> x,sum+=x;
    for(auto &x:b)cin >> x,sum-=x;
    if(sum!=0)return void(cout << -1 << '\n');
    vector<int> in,de;
    for(int i=0;i<n;i++){
        while(a[i]<b[i]){
            in.emplace_back(i+1);
            a[i]++;
        }
        while(a[i]>b[i]){
            de.emplace_back(i+1);
            a[i]--;
        }
    }
    if(de.size()!=in.size())return void(cout << -1 << '\n');
    cout << in.size() << '\n';
    for(int i=0;i<in.size();i++){
        cout << de[i] << ' ' << in[i] << '\n';
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}