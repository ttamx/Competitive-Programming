#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    int N, tmp_val;
    cin>>N;
    int back[N], val[N], current_last=-1;
    vector<int> value, index;
    for (int i=0; i<N; i++)
    {
        cin>>tmp_val;
        val[i]=tmp_val;
        auto itr=lower_bound(value.begin(), value.end(), tmp_val);
        int location=itr-value.begin();
        if (location==value.size())
        {
            value.push_back(tmp_val);
            index.push_back(i);
            current_last=i;
            if (location!=0)
                back[i]=index[location-1];
            else
                back[i]=i;
        }
        else
        {
            value[location]=tmp_val;
            index[location]=i;
            if (location==0)
                back[i]=i;
            else
                back[i]=index[location-1];
        }
    }
    vector<int> ans;
    int i=current_last;
    while (back[i]!=i)
    {
        ans.push_back(val[i]);
        i=back[i];
    }
    ans.push_back(val[i]);
    cout<<ans.size() << '\n';
    reverse(ans.begin(), ans.end());
    for (auto a:ans)
        cout<<a<<' ';
}