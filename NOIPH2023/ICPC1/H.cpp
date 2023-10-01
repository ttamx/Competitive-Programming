#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> v(n),c(n);
    int sum=0;
    for(auto &x:v)cin >> x,sum+=x;
    for(auto &x:c)cin >> x;
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            for(int k=0;k<j;k++){
                if(c[i]+c[j]+c[k]>=sum){
                    cout << "YES";
                    return 0;
                }
            }
        }
    }
    cout << "NO";
}