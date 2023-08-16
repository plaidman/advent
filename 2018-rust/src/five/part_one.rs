use super::polymer::traverse_polymer;

pub fn run(line: Vec<char>) {
    let len = traverse_polymer(line);

    println!("reacted polymer length: {}", len);
}
