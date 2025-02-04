// submission for https://oj.vnoi.info/problem/trie_tquery
struct Trie {
  const int MAX_BIT = 30;
  struct TrieNode {
    TrieNode* child[2];
    int cnt;
    int64_t sum;
    TrieNode() {
      for (int i = 0; i < 2; i++) {
        child[i] = NULL;
      }
      cnt = 0;
      sum = 0;
    }
  };
  TrieNode* root = new TrieNode();
  void add(int x, int delta) {
    TrieNode* u = root;
    u->cnt += delta;
    u->sum += x * delta;
    for (int i = MAX_BIT; i >= 0; i--) {
      int id = x >> i & 1;
      if (u->child[id] == NULL) {
        u->child[id] = new TrieNode();
      }
      u = u->child[id];
      u->cnt += delta;
      u->sum += x * delta;
    }
  }
  bool find(int x) {
    TrieNode* u = root;
    for (int i = MAX_BIT; i >= 0; i--) {
      int id = x >> i & 1;
      if (u->child[id] == NULL) {
        return false;
      }
      u = u->child[id];
    }
    return u->cnt > 0;
  }
  int kth(int k) {
    int ans = 0;
    TrieNode* u = root;
    for (int i = MAX_BIT; i >= 0; i--) {
      if (u->child[0] != NULL) {
        if (k <= u->child[0]->cnt) {
          u = u->child[0];
          continue;
        } else {
          k -= u->child[0]->cnt;
        }
      }
      if (u->child[1] == NULL) {
        break;
      }
      ans |= 1ll << i;
      u = u->child[1];
    }
    return ans;
  }
  int64_t sum_smaller_than(int x) {
    if (x < 0) {
      return 0;
    }
    TrieNode* u = root;
    int64_t ans = 0;
    for (int i = MAX_BIT; i >= 0; i--) {
      int id = x >> i & 1;
      if (id) {
        if (u->child[id ^ 1] != NULL) {
          ans += u->child[id ^ 1]->sum;
        }
      }
      if (u->child[id] == NULL) {
        return ans;
      }
      u = u->child[id];
    }
    return ans + u->sum;
  }
  int max_xor(int x) {
    TrieNode* u = root;
    int ans = 0;
    for (int i = MAX_BIT; i >= 0; i--) {
      int id = x >> i & 1;
      if (u->child[id ^ 1] != NULL && u->child[id ^ 1]->cnt > 0) {
        u = u->child[id ^ 1];
        ans |= 1 << i;
        continue;
      }
      if (u->child[id] == NULL) {
        break;
      }
      u = u->child[id];
    }
    return ans;
  }
};
