use super::event::Event;
use super::nap::Nap;
use core::fmt::Debug;
use std::collections::HashMap;

pub struct Guard {
    id: usize,
    pub events: Vec<Event>,
    days: HashMap<usize, Vec<Nap>>
}

impl Debug for Guard {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "guard {}:", self.id)?;

        writeln!(f, "  events:")?;
        for event in self.events.iter() {
            writeln!(f, "    {:?}:", event)?;
        }

        writeln!(f, "  naps:")?;
        for (_, day) in self.days.iter() {
            for nap in day.iter() {
                writeln!(f, "    {:?}:", nap)?;
            }
        }
        
        Ok(())
    }
}

impl Guard {
    pub fn new(id: usize) -> Guard {
        Guard { id, events: Vec::new(), days: HashMap::new() }
    }
    
    pub fn populate_days(&mut self) {
        let mut event_iter = self.events.iter().peekable();

        while event_iter.peek().is_some() {
            let start = event_iter.next().unwrap();
            let end = event_iter.next().unwrap();
            
            let naps = self.days.entry(start.get_day_stamp()).or_insert(Vec::new());
            naps.push(Nap::new(start.minute, end.minute));
        }
    }
}