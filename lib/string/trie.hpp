#pragma once
/**
 * @file trie.hpp
 * @brief trie木に関するコード。
 * @details
 * * 使用コンテスト
 *  * https://atcoder.jp/contests/abc287/submissions/41215033
 */

#include <vector>

/**
 * @brief Trie木を表すクラス。
 * 
 * @tparam char_size アルファベットの数。
 * @tparam base 最初のアルファベット。
 */
template <int char_size, int base>
class Trie {
  class TrieNode {
  public:
    std::vector<int> next;
    std::vector<int> accept;
    int c;
    int common;

    TrieNode(int c) : c(c), common(0) {
      next.assign(char_size, -1);
    }
  };
  std::vector<TrieNode> nodes;
  int root;

  void insert(const string &word, int word_id) {
    int node_id = 0;
    for (int i = 0; i < word.size(); ++i) {
      int c = word[i] - base;
      int &next_id = nodes[node_id].next[c];
      if (next_id == -1) {
        next_id = nodes.size();
        nodes.push_back(TrieNode(c));
      }
      ++nodes[node_id].common;
      node_id = next_id;
    }
    ++nodes[node_id].common;
    nodes[node_id].accept.push_back(word_id);
  }

public:
  Trie() : root(0) {
    nodes.push_back(TrieNode(root));
  }

  /**
   * @brief 単語をTrie木に挿入する。O(単語長)。
   * @param word 挿入する単語。
   */
  void insert(const string &word) {
    insert(word, nodes[0].common);
  }

  /**
   * @brief 単語がTrie木に含まれるか検索する。O(単語長)。
   * @param word 検索する単語。
   * @param prefix wordを接頭辞とする単語の存在を検索する場合はtrue、wordそのものを検索する場合はfalse。
   * @return word(を接頭辞とする単語)がTrie木に含まれる場合はtrue、そうでない場合はfalse。
   */
  bool search(const string &word, bool prefix = false) const {
    int node_id = 0;
    for (int i = 0; i < word.size(); ++i) {
      int c = word[i] - base;
      int next_id = nodes[node_id].next[c];
      if (next_id == -1) {
        return false;
      }
      node_id = next_id;
    }
    return (prefix ? true : nodes[node_id].accept.size() > 0);
  }

  /**
   * @brief Trie木に含まれる単語の総数を返す。
   * @return Trie木に含まれる単語の総数。
   */
  int count() const {
    return nodes[0].common;
  }

  /**
   * @brief Trie木に含まれる単語とwordとのLCPの長さの最大値を返す。
   * @param word LCPの長さを計算する文字列。
   * @return 最大のLCPの長さ。
   */
  int lcp_length(const string &word) const {
    int node_id = 0;
    for (int i = 0; i < word.size(); ++i) {
      int c = word[i] - base;
      int next_id = nodes[node_id].next[c]; // i文字目を表すノードのid
      if (next_id == -1 || nodes[next_id].common == 1) {
        return i;
      }
      node_id = next_id;
    }
    return word.size();
  }
}; // class Trie