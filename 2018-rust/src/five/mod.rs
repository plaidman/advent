mod part_one;
mod part_two;
mod polymer;

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
    let mut line = String::new();
    BufReader::new(file).read_line(&mut line).ok();

    parts[part - 1](Vec::from_iter(line.chars()));
}
