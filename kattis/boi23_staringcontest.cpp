#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

mt19937 rng(time(nullptr));

const int N=1505;

int n;
int pre;
p2 cur;
int ans[N];

int ask(int i,int j){
    cout << "? " << i << " " << j << endl;
    int res;
    cin >> res;
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    vector<int> a(n);
    iota(a.begin(),a.end(),1);
    shuffle(a.begin(),a.end(),rng);
    for(int i=0;i<n;i++){
        if(ans[a[i]])continue;
        int idx=0;
        for(int j=i+1;j<n;j++){
            if(ans[a[j]])continue;
            int res=ask(a[i],a[j]);
            if(res==ans[a[i]]){
                ans[idx]=0;
                break;
            }
            if(res>ans[a[i]]){
                ans[a[i]]=res;
                idx=a[j];
            }
            ans[a[j]]=res;
        }
    }
    cout << "!";
    for(int i=1;i<=n;i++)cout << " " << ans[i];
    cout << endl;
}