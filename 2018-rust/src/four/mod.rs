mod event;

use std::{ io::{BufReader, BufRead }, fs::File };
use event::Event;

pub fn run(_part: usize, filename: String) {
    let file = File::open(filename).expect("failed to open file");
    let mut events: Vec<Event> = BufReader::new(file).lines().map(
        |i| i.unwrap().parse::<Event>().unwrap()
    ).collect();
    
    events.sort();

    println!("{:#?}", events);
}