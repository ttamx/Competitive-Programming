#include "template.hpp"
#include "string/z-algorithm.hpp"

void runcase(){
    string s;
    cin >> s;
    int n=s.size();
    if(n%2)return void(cout << "0\n");
    auto t=s;
    reverse(t.begin(),t.end());
    auto a=z_algorithm(s),b=z_algorithm(t);
    int ans=0;
    for(int i=0;i<=n;i+=2){
        if(a[i/2]<i/2)continue;
        if(b[(n-i)/2]<(n-i)/2)continue;
        ans++;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}