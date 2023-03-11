#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;
class huffman_tree {
  protected:

    class huffman_node {
      public:
        char letter;
        int freq;
        huffman_node *left, *right;
        huffman_node() : letter('*'),freq(0),left(NULL),right(NULL) {}
        huffman_node(char letter,int freq,huffman_node *left,huffman_node *right) : 
          letter(letter),freq(freq), left(left),right(right) {}
        bool is_leaf() { return left == NULL && right == NULL;  }
    };
    class node_comparator {
      public:
        bool operator()(const huffman_node *a, const huffman_node *b) {
          return a->freq > b->freq;
        }
    };

    huffman_node *root;
    void build_tree(vector<huffman_node*> data) {
      priority_queue<huffman_node*,vector<huffman_node*>,node_comparator> pq;
      for (auto &x : data) pq.push(x);
      while (pq.size() > 1) {
        huffman_node *right = pq.top(); pq.pop();
        huffman_node *left = pq.top(); pq.pop();
        pq.push(new huffman_node('*',left->freq+right->freq,left,right));
      }
      root = pq.top();
    }

  public:
    huffman_tree(string s) {
      map<char,int> count;
      for (auto &c : s) 
        count[c]++;
      vector<huffman_node*> nodes;
      for (auto &x : count) 
        nodes.push_back(new huffman_node(x.first,x.second,NULL,NULL));
      build_tree(nodes);
    }

    map<char,vector<bool>> build() {
      map<char,vector<bool>> m;
      return m;
    }
};

int main() {
  string s = "never gonna give you up never gonna give you down never gonna run around and desert you";
  huffman_tree ht(s);

  map<char,vector<bool>> m = ht.build();
}



