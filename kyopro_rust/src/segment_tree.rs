use cargo_snippet::snippet;

// validation
// 修正後
// Point Add Range Sum https://judge.yosupo.jp/submission/194523
// 修正前でバグを踏んでいなかっただけのもの
// Static RMQ (RMQ専用): https://judge.yosupo.jp/submission/194451
// Static RMQ (一般化): https://judge.yosupo.jp/submission/194458
#[snippet("snipsegmenttree")]
pub mod segment_tree {
    pub struct SegmentTree<'a, T: Copy> {
        nodes: Vec<T>,
        unit_elem: T,
        op: Box<dyn Fn(T, T) -> T + 'a>,
        first_leaf: usize,
    }

    impl<'a, T: Copy> SegmentTree<'a, T> {
        pub fn new(leaves: &Vec<T>, unit_elem: &T, op: Box<dyn Fn(T, T) -> T + 'a>) -> Self {
            let mut n_leaves = 1;
            while n_leaves < leaves.len() {
                n_leaves *= 2;
            }
            let first_leaf = n_leaves - 1;
            let mut nodes = vec![*unit_elem; n_leaves * 2 - 1];
            for i in 0..leaves.len() {
                nodes[first_leaf + i] = leaves[i];
            }
            for i in (0..first_leaf).rev() {
                let left_child = nodes[2 * i + 1];
                let right_child = nodes[2 * i + 2];
                nodes[i] = op(left_child, right_child);
            }
            SegmentTree {
                nodes,
                unit_elem: *unit_elem,
                op,
                first_leaf,
            }
        }

        pub fn update(&mut self, leaf_id: usize, val: T) {
            let mut node_id = self.first_leaf + leaf_id;
            self.nodes[self.first_leaf + leaf_id] = val;
            while node_id > 0 {
                node_id = (node_id - 1) / 2;
                let left_child = self.nodes[2 * node_id + 1];
                let right_child = self.nodes[2 * node_id + 2];
                self.nodes[node_id] = (self.op)(left_child, right_child);
            }
        }

        pub fn get_val(&self, leaf_id: usize) -> T {
            self.nodes[self.first_leaf + leaf_id]
        }

        pub fn query(&self, left: usize, right: usize) -> T {
            self.query_inner(left, right, 0, 0, self.first_leaf + 1)
        }

        fn query_inner(
            &self,
            query_left: usize,
            query_right: usize,
            node_id: usize,
            node_left: usize,
            node_right: usize,
        ) -> T {
            if node_right <= query_left || query_right <= node_left {
                return self.unit_elem;
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
            (self.op)(left_val, right_val)
        }
    }
}
