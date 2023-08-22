use super::node::Node;

pub fn run(numbers: Vec<usize>) {
    let mut root = Node::new();
    root.parse(&numbers);
    println!("sum: {}", root.value_one());
}
