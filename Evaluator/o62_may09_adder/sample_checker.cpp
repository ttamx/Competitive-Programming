#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;

ifstream infile; // argv[1]    input file
ifstream outfile;// argv[2]    student output file
ifstream ansfile;// argv[3]    real output from judge

#define OK "Correct"
#define WRONG "Incorrect"
#define COMMENT "Comment"

int fullScore = 10;

template <typename T>
void report(string result,T score) {
  cout << result << endl;
  cout << score << endl;
  exit(0);
}

template <typename T>
void report_comment(T comment,int score) {
  cout << "Comment:[" << comment << "]" << endl;
  cout << score << endl;
  exit(0);
}


void report(string result) {
  if (result == WRONG)
    report(result,0);
  if (result == OK)
    report(result,fullScore);
}


//------------------------------------ judge --------------------------------

class Node {
  public:
  int i1,i2;
  vector<int> output;
  int type; // 0,1,2 = and / or / not
  int depth,result;
};

int n;
int m;
vector<int> o,a,b,c;

vector<Node> nodes;

//vector for evaluations of the logic
vector<int> va(n),vb(n),vans(n+1);
int vc;

void read_input() {
  infile >> n >> m;
  o.resize(n+1);
  a.resize(n);
  b.resize(n);
  c.resize(1);

  int om;
  outfile >> om;
  if (om > m) {
    report_comment("too much gate",0);
  }
  nodes.resize(om+1);
  for (int i = 0;i <= n;i++) {
    outfile  >> o[i];
    if (o[i] < -2*n || o[i] > om)
      report_comment("BAD GATE NUMBER",0);
  }
  for (int i = 0;i <= om;i++) {
    nodes[i].depth = -1;
  }
  for (int i = 1;i <= om;i++) {
    string st;
    int i1,i2;
    outfile >> st;
    //cerr << "read " << st << endl;
    if (st == "AND") {
      outfile >> i1 >> i2;
      if (i1 < -2*n || i1 > om || i2 < -2*n || i2 > om) 
        report_comment("BAD GATE INPUT",0);
      //cerr << "read " << i1 << i2 << endl;
      nodes[i].i1 = i1;
      nodes[i].i2 = i2;
      nodes[i].type = 0;
      if (i1 > 0) nodes[i1].output.push_back(i);
      if (i2 > 0) nodes[i2].output.push_back(i);
    } else if (st == "OR") {
      outfile >> i1 >> i2;
      if (i1 < -2*n || i1 > om || i2 < -2*n || i2 > om) 
        report_comment("BAD GATE INPUT",0);
      //cerr << "read " << i1 << i2 << endl;
      nodes[i].i1 = i1;
      nodes[i].i2 = i2;
      nodes[i].type = 1;
      if (i1 > 0) nodes[i1].output.push_back(i);
      if (i2 > 0) nodes[i2].output.push_back(i);
    } else if (st == "NOT") {
      outfile >> i1;
      if (i1 < -2*n || i1 > om || i2 < -2*n || i2 > om) 
        report_comment("BAD GATE INPUT",0);
      //cerr << "read " << i1 << endl;
      nodes[i].i1 = i1;
      nodes[i].type = 2;
      if (i1 > 0) nodes[i1].output.push_back(i);
    } else {
      report_comment("BAD GATE TYPE",0);
    }
  }
}

int depth(int idx) {

  if (idx <= 0) return -1;
  if (nodes[idx].depth > -1) return nodes[idx].depth;
  if (nodes[idx].type == 2) return depth(nodes[idx].i1) + 1;
  nodes[idx].depth = (max(depth(nodes[idx].i1),depth(nodes[idx].i2)) + 1);
  return nodes[idx].depth;
}

int calculate_depth() {
  int d = -1;
  for (int i = 0;i <= n;i++) {
    int tmp = depth(o[i]);
    d = max(tmp,d);
  }
  return d;
}

int cal(int idx) {
  if (idx == 0) return vc;
  if (idx < 0 && idx >= -n) return va[-idx - 1];
  if (idx < -n) return vb[-idx - n - 1];
  if (nodes[idx].result > -1) return nodes[idx].result;
  if (nodes[idx].type == 0) { //and
    int a = cal(nodes[idx].i1);
    int b = cal(nodes[idx].i2);
    nodes[idx].result = ((a && b) ? 1 : 0);
    //cerr << " nodes " << idx << " result = " << nodes[idx].result << endl;
    return nodes[idx].result;
  } else if (nodes[idx].type == 1) { //or
    int a = cal(nodes[idx].i1);
    int b = cal(nodes[idx].i2);
    nodes[idx].result = ((a || b) ? 1 : 0);
    //cerr << " nodes " << idx << " result = " << nodes[idx].result << endl;
    return nodes[idx].result;
  } else {
    int a = cal(nodes[idx].i1); //not
    nodes[idx].result = ((a == 0) ? 1 : 0);
    //cerr << " nodes " << idx << " result = " << nodes[idx].result << endl;
    return nodes[idx].result;
  }
}

bool check(vector<int> &vans) {
  for (auto &x : nodes) x.result = -1;
  for (int i = 0;i <= n;i++) {
    int bit = cal(o[i]);
    cerr << bit << " ";
    //cerr << "output for bit " << i << ": " << bit << endl;
    if (bit != vans[i]) return false;
  }
  cerr << "\n";
  return true;
}


int main(int argc, char** argv) {
  infile.open(argv[1]);  // input
  outfile.open(argv[2]); // output of student
  ansfile.open(argv[3]); // real solution from judge

  read_input();
  int d = calculate_depth();

  //check
  int k;
  ansfile >> k;

  for (int i = 0;i < k;i++) {
    string a,b,c,ans;
    ansfile >> a >> b >> c >> ans;
    va.resize(n);
    vb.resize(n);
    vans.resize(n+1);

    cerr << "case " << i << endl;
    cerr << "a = " << a << endl;
    cerr << "b = " << b << endl;
    cerr << "c = " << c << endl;
    cerr << "d = " << ans << endl;

    for (int i = 0;i < n;i++) {
      va[i] = a[i] == '0' ? 0 : 1;
      vb[i] = b[i] == '0' ? 0 : 1;
      vans[i] = ans[i] == '0' ? 0 : 1;
    }
    vc = c[0] == '0' ? 0 : 1;
    vans[n] = ans[n] == '0' ? 0 : 1;
    bool result = check(vans);

    if (!result) {
      report(WRONG);
    }
  }
  report_comment(d,fullScore);
}

