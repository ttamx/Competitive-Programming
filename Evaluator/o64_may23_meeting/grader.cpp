#include "meeting.cpp"
#include <vector>
#include <cstdio>

using namespace std;

static int a[100003],b[100003],c[100003],ui[100003],vi[100003],length[100003];

int main()
{
  int N,Q;
  scanf("%d %d",&N,&Q);
  vector<vector<int>>roads;
  vector<int>lengths,as,bs,cs;
  for(int i = 0;i < N-1;i++) {
    scanf("%d %d %d",&ui[i],&vi[i],&length[i]);
    vector<int>tmp;
    tmp.emplace_back(ui[i]);
    tmp.emplace_back(vi[i]);
    roads.emplace_back(tmp);
    lengths.emplace_back(length[i]);
  }
  for(int i = 0;i < Q;i++) {
    scanf("%d %d %d",&a[i],&b[i],&c[i]);
    as.emplace_back(a[i]);
    bs.emplace_back(b[i]);
    cs.emplace_back(c[i]);
  }

  vector<int>ans = best_meeting(N,Q,roads,lengths,as,bs,cs);

  for(int i = 0;i < ans.size();i++) {
    printf("%d\n",ans[i]);
  }
}
