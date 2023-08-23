mod part_one;
mod part_two;

use regex_lite::Regex;
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

    let regex = Regex::new(r"^(\d+) players; last marble is worth (\d+) points$").unwrap();
    let (num_players, num_marbles) = regex
        .captures(&line)
        .and_then(|cap| {
            Some((
                cap[1].parse::<usize>().unwrap(),
                cap[2].parse::<usize>().unwrap(),
            ))
        })
        .unwrap();

    parts[part - 1](num_players, num_marbles);
}
