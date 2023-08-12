mod part_one;
mod part_two;

use std::{ io::{ BufReader, BufRead }, fs::File };

pub fn run(part: usize, filename: String) {
    let parts = [part_one::run, part_two::run];

    if part > parts.len() {
        println!("usage: cargo run <day.part> <input>");
        println!("  <part> cannot be greater than {}", parts.len());
        return;
    }
    
    let file = File::open(filename).expect("failed to open file");
    let lines: Vec<String> = BufReader::new(file).lines().map(|i| i.unwrap()).collect();
    
    parts[part-1](lines);
}
