mod event;
mod guard;
mod nap;

use event::Event;
use guard::Guard;
use std::collections::HashMap;
use std::{
    fs::File,
    io::{BufRead, BufReader},
};

pub fn run(_part: usize, filename: String) {
    let file = File::open(filename).expect("failed to open file");
    let mut events: Vec<Event> = BufReader::new(file)
        .lines()
        .map(|line| line.unwrap().parse::<Event>().unwrap())
        .collect();

    events.sort();
    // println!("{:#?}", events);

    let mut guards = HashMap::<usize, Guard>::new();
    let mut cur_guard = &mut Guard::new(0);

    for event in events {
        if event.guard_id.is_some() {
            let guard_id = event.guard_id.unwrap();
            cur_guard = guards.entry(guard_id).or_insert(Guard::new(guard_id));
        } else {
            cur_guard.events.push(event);
        }
    }

    for (_, guard) in guards.iter_mut() {
        guard.populate_days();
        guard.find_sleepiest_minute();
    }

    // part one
    let mut sleepiest_guard = &Guard::new(0);
    for (_, guard) in guards.iter() {
        if sleepiest_guard.total_sleep < guard.total_sleep {
            sleepiest_guard = guard;
        }
    }
    let (minute, _) = sleepiest_guard.sleepiest_minute;
    println!("part one: {}", minute * sleepiest_guard.id);

    // part two
    let mut sleepiest_guard = &Guard::new(0);
    for (_, guard) in guards.iter() {
        let (_, days) = guard.sleepiest_minute;
        let (_, sl_days) = sleepiest_guard.sleepiest_minute;

        if sl_days < days {
            sleepiest_guard = guard;
        }
    }
    let (minute, _) = sleepiest_guard.sleepiest_minute;
    println!("part two: {}", minute * sleepiest_guard.id);
}
