mod event;
mod guard;
mod nap;

use std::{ io::{BufReader, BufRead }, fs::File };
use std::collections::HashMap;
use event::Event;
use guard::Guard;

pub fn run(_part: usize, filename: String) {
    let file = File::open(filename).expect("failed to open file");
    let mut events: Vec<Event> = BufReader::new(file).lines().map(
        |line| line.unwrap().parse::<Event>().unwrap()
    ).collect();

    events.sort();
    // println!("{:#?}", events);
    
    let mut guards = HashMap::<usize, Guard>::new();
    let mut cur_guard = &mut Guard::new(0);

    for event in events {
        if event.guard_id.is_some() {
            let guard_id = event.guard_id.unwrap();
            cur_guard = guards.entry(guard_id).or_insert(Guard::new(guard_id));
        } else  {
            cur_guard.events.push(event);
        }
    }

    for (_, guard) in guards.iter_mut() {
        guard.populate_days();
        guard.find_sleepiest_minute();
    }
    println!("{:#?}", guards);
}