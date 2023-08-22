pub struct Node {
    children: Vec<Node>,
    metadata: Vec<usize>,
}

impl Node {
    pub fn new() -> Node {
        Node {
            children: Vec::new(),
            metadata: Vec::new(),
        }
    }

    pub fn value_one(&self) -> usize {
        let children = self.children.iter().map(|c| c.value_one()).sum::<usize>();
        let metadata = self.metadata.iter().sum::<usize>();

        children + metadata
    }

    pub fn value_two(&self) -> usize {
        if self.children.len() == 0 {
            let sum = self.metadata.iter().sum();
            return sum;
        }

        let mut sum = 0;
        for &value in self.metadata.iter() {
            let child_opt = self.children.get(value - 1);

            if child_opt.is_none() {
                continue;
            }

            let child = child_opt.unwrap();
            sum += child.value_two();
        }

        sum
    }

    pub fn parse<'a>(&mut self, numbers: &'a [usize]) -> &'a [usize] {
        let mut remainder = numbers;

        let num_nodes = remainder[0];
        let num_meta = remainder[1];

        (_, remainder) = remainder.split_at(2);

        for _ in 0..num_nodes {
            let mut new_node = Node::new();
            remainder = new_node.parse(remainder);
            self.children.push(new_node);
        }

        let (metadata, meta_remainder) = remainder.split_at(num_meta);
        remainder = meta_remainder;
        for &value in metadata {
            self.metadata.push(value);
        }

        remainder
    }
}
