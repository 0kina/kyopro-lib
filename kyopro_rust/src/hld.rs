use cargo_snippet::snippet;

// validation
// Vertex Add Path Sum (https://judge.yosupo.jp/submission/195316)
#[snippet("sniphld")]
pub mod hld {
    pub struct HLD<'a> {
        hld_seq: Vec<usize>,
        hld_orders: Vec<usize>,
        most_shallow_list: Vec<usize>,
        size: Vec<u32>,
        depth: Vec<u32>,
        parents: &'a Vec<usize>,
    }

    impl<'a> HLD<'a> {
        fn calc_size(&mut self, x: usize, children_list: &Vec<Vec<usize>>) -> u32 {
            if self.size[x] != 0 {
                return self.size[x];
            }
            self.size[x] = 1;
            for c in children_list[x].iter() {
                self.size[x] += self.calc_size(*c, children_list);
            }
            self.size[x]
        }

        fn calc_depth(&mut self, x: usize, children_list: &Vec<Vec<usize>>) {
            for c in children_list[x].iter() {
                self.depth[*c] = self.depth[x] + 1;
                self.calc_depth(*c, children_list);
            }
        }

        /// `tree`は第`i`頂点の親を格納した`Vec`であり，`tree[根] == tree.len()`が必要．
        pub fn new(tree: &'a Vec<usize>) -> HLD {
            let n = tree.len();
            let mut children_list = vec![vec![]; n];
            let mut root = n;
            for (i, p) in tree.iter().enumerate() {
                if *p == n {
                    assert_eq!(root, n);
                    root = i;
                    continue;
                }
                children_list[*p].push(i);
            }
            assert_ne!(root, n);
            let mut hld = HLD {
                hld_seq: vec![],
                hld_orders: vec![n; n],
                most_shallow_list: vec![n; n],
                size: vec![0; n],
                depth: vec![0; n],
                parents: tree,
            };
            hld.calc_size(root, &children_list);
            hld.calc_depth(root, &children_list);
            hld.construct(root, root, &children_list);
            hld
        }

        fn construct(&mut self, x: usize, most_shallow: usize, children_list: &Vec<Vec<usize>>) {
            self.hld_orders[x] = self.hld_seq.len();
            self.hld_seq.push(x);
            self.most_shallow_list[x] = most_shallow;

            if children_list[x].len() == 0 {
                return;
            }
            let mut heavy_child = (self.hld_orders.len(), 0);
            for c in children_list[x].iter() {
                if self.size[*c] > heavy_child.1 {
                    heavy_child = (*c, self.size[*c]);
                }
            }
            self.construct(heavy_child.0, most_shallow, children_list);

            for c in children_list[x].iter() {
                if *c == heavy_child.0 {
                    continue;
                }
                self.construct(*c, *c, children_list);
            }
        }

        pub fn hld(&self) -> &Vec<usize> {
            &self.hld_seq
        }

        pub fn index(&self, x: usize) -> usize {
            self.hld_orders[x]
        }

        /// 分割されたクエリは閉区間であることに注意
        pub fn query(&self, mut u: usize, mut v: usize) -> Vec<(usize, usize)> {
            let mut ret = vec![];
            while self.most_shallow_list[u] != self.most_shallow_list[v] {
                let top_u = self.most_shallow_list[u];
                let top_v = self.most_shallow_list[v];
                if self.depth[top_u] <= self.depth[top_v] {
                    ret.push((self.hld_orders[top_v], self.hld_orders[v]));
                    v = self.parents[top_v];
                } else {
                    ret.push((self.hld_orders[top_u], self.hld_orders[u]));
                    u = self.parents[top_u];
                }
            }
            ret.push((
                std::cmp::min(self.hld_orders[u], self.hld_orders[v]),
                std::cmp::max(self.hld_orders[u], self.hld_orders[v]),
            ));
            ret
        }
    }

    #[cfg(test)]
    mod test_hld {
        use super::*;

        #[test]
        fn test_hld_query() {
            // https://qiita.com/Pro_ktmr/items/4e1e051ea0561772afa3の例を使用
            let tree = vec![12, 0, 1, 2, 2, 1, 0, 6, 7, 7, 0, 10];
            let hld = HLD::new(&tree);
            assert_eq!(hld.query(4, 9), vec![(9, 9), (4, 4), (6, 7), (0, 2)]);
        }
    }
}
