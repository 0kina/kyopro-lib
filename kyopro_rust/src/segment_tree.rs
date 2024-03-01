use cargo_snippet::snippet;

// validate
// Static RMQ: https://judge.yosupo.jp/submission/194451
#[snippet("snipsegmenttree")]
pub mod segment_tree {
    pub struct SegmentTree {
        nodes: Vec<i64>,
        first_leaf: usize,
    }

    impl SegmentTree {
        pub fn new(leaves: &Vec<i64>) -> Self {
            let mut n_leaves = 1;
            while n_leaves < leaves.len() {
                n_leaves *= 2;
            }
            let first_leaf = n_leaves - 1;
            let mut nodes = vec![1e18 as i64; n_leaves * 2 - 1];
            for i in 0..leaves.len() {
                nodes[first_leaf + i] = leaves[i];
            }
            for i in (0..first_leaf).rev() {
                let left_child = nodes[2 * i + 1];
                let right_child = nodes[2 * i + 2];
                nodes[i] = std::cmp::min(left_child, right_child);
            }
            SegmentTree { nodes, first_leaf }
        }

        pub fn update(&mut self, mut leaf_id: usize, val: i64) {
            self.nodes[self.first_leaf + leaf_id] = val;
            while leaf_id > 0 {
                leaf_id = (leaf_id - 1) / 2;
                let left_child = self.nodes[2 * leaf_id + 1];
                let right_child = self.nodes[2 * leaf_id + 2];
                self.nodes[leaf_id] = std::cmp::min(left_child, right_child);
            }
        }

        pub fn query(&self, left: usize, right: usize) -> i64 {
            self.query_inner(left, right, 0, 0, self.first_leaf + 1)
        }

        pub fn query_inner(
            &self,
            query_left: usize,
            query_right: usize,
            node_id: usize,
            node_left: usize,
            node_right: usize,
        ) -> i64 {
            if node_right <= query_left || query_right <= node_left {
                return 1e18 as i64;
            }
            if query_left <= node_left && node_right <= query_right {
                return self.nodes[node_id];
            }
            let left_val = self.query_inner(
                query_left,
                query_right,
                2 * node_id + 1,
                node_left,
                (node_left + node_right) / 2,
            );
            let right_val = self.query_inner(
                query_left,
                query_right,
                2 * node_id + 2,
                (node_left + node_right) / 2,
                node_right,
            );
            std::cmp::min(left_val, right_val)
        }
    }
}
