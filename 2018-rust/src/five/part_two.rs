use super::polymer::traverse_polymer;

pub fn run(line: Vec<char>) {
    let mut shortest = 999999;

    for exclude in "abcdefghijklmnopqrstuvwxyz".chars() {
        let filtered: Vec<char> = line
            .iter()
            .filter(|l| l.to_ascii_uppercase() != exclude && l.to_ascii_lowercase() != exclude)
            .map(|l| *l)
            .collect();

        let len = traverse_polymer(filtered);
        if len < shortest {
            shortest = len;
        }
    }

    println!("shortest polymer: {}", shortest);
}
