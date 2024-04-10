use cargo_snippet::snippet;

// validation
// ABC348 E (https://atcoder.jp/contests/abc348/submissions/52226059)
#[snippet("sniprerooting")]
pub mod rerooting {
    pub struct Rerooting<'a, T: Copy + std::fmt::Debug> {
        /// 頂点`i`から出る第`j`辺に対応するDPの値
        dp: Vec<Vec<T>>,
        /// 頂点`i`に対するクエリの答え
        ans: Vec<T>,
        identity: T,
        merge: Box<dyn Fn(T, T) -> T + 'a>,
        add_root: Box<dyn Fn(T, usize) -> T + 'a>,
    }
    impl<'a, T: Copy + std::fmt::Debug> Rerooting<'a, T> {
        pub fn new(
            adj_list: &Vec<Vec<usize>>,
            identity: T,
            merge: Box<dyn Fn(T, T) -> T + 'a>,
            add_root: Box<dyn Fn(T, usize) -> T + 'a>,
        ) -> Rerooting<'a, T> {
            let n = adj_list.len();
            let mut dp = Vec::with_capacity(n);
            for i in 0..n {
                dp.push(vec![identity; adj_list[i].len()]);
            }
            let mut ret = Rerooting {
                dp,
                ans: vec![identity; n],
                identity,
                merge,
                add_root,
            };
            ret.ans[0] = ret.tree_dp(0, n, adj_list);
            ret.reroot(0, n, identity, adj_list);
            ret
        }
        fn tree_dp(&mut self, node: usize, parent: usize, adj_list: &Vec<Vec<usize>>) -> T {
            let mut merged_val = self.identity;
            for (i, &child) in adj_list[node].iter().enumerate() {
                if child == parent {
                    continue;
                }
                self.dp[node][i] = self.tree_dp(child, node, adj_list);
                merged_val = (self.merge)(merged_val, self.dp[node][i]);
            }
            (self.add_root)(merged_val, node)
        }
        /// `root`に隣接する頂点へのクエリを計算．`dp_val`は辺`(root, parent)`に対するDP値
        fn reroot(&mut self, root: usize, parent: usize, dp_val: T, adj_list: &Vec<Vec<usize>>) {
            let degree = adj_list[root].len();
            let mut left_acc = vec![self.identity; degree + 1];
            for i in 1..=degree {
                if adj_list[root][i - 1] == parent {
                    self.dp[root][i - 1] = dp_val;
                }
                left_acc[i] = (self.merge)(left_acc[i - 1], self.dp[root][i - 1]);
            }
            let mut right_acc = vec![self.identity; degree + 1];
            for i in (0..degree).rev() {
                right_acc[i] = (self.merge)(right_acc[i + 1], self.dp[root][i]);
            }
            self.ans[root] = (self.add_root)(left_acc[degree], root);
            for (i, &child) in adj_list[root].iter().enumerate() {
                if child == parent {
                    continue;
                }
                let merged_val = (self.merge)(left_acc[i], right_acc[i + 1]);
                self.reroot(child, root, (self.add_root)(merged_val, root), adj_list);
            }
        }
        pub fn answers(&self) -> &Vec<T> {
            &self.ans
        }
    }
}
