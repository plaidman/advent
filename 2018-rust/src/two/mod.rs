mod part_one;
mod part_two;

use std::{
    fs::File,
    io::{BufRead, BufReader},
};

pub fn run(part: usize, filename: String) {
    let parts = [part_one::run, part_two::run];

    if part > parts.len() {
        println!("usage: cargo run <day.part> <input>");
        println!("  <part> cannot be greater than {}", parts.len());
        return;
    }

    let file = File::open(filename).expect("failed to open file");
    let lines: Vec<Vec<char>> = BufReader::new(file)
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    parts[part - 1](lines);
}
