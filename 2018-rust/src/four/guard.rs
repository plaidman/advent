use super::event::Event;
use super::nap::Nap;
use core::fmt::Debug;

pub struct Guard {
    id: usize,
    pub events: Vec<Event>,
    naps: Vec<Nap>,
    total_sleep: usize,
    sleepiest_minute: (usize, usize),
}

impl Debug for Guard {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "guard {}:", self.id)?;

        // writeln!(f, "  events:")?;
        // for event in self.events.iter() {
        //     writeln!(f, "    {:?}", event)?;
        // }

        // writeln!(f, "  naps:")?;
        // for nap in self.naps.iter() {
        //     writeln!(f, "    {:?}", nap)?;
        // }
        
        writeln!(f, "  sleepiest minute: {:?}", self.sleepiest_minute)?;
        writeln!(f, "  total_sleep: {}", self.total_sleep)?;
        
        Ok(())
    }
}

impl Guard {
    pub fn new(id: usize) -> Guard {
        Guard { id, events: Vec::new(), naps: Vec::new(), total_sleep: 0, sleepiest_minute: (0,0) }
    }
    
    pub fn populate_days(&mut self) {
        let mut event_iter = self.events.iter().peekable();

        while event_iter.peek().is_some() {
            let start = event_iter.next().unwrap();
            let end = event_iter.next().unwrap();
            
            let new_nap = Nap::new(start.minute, end.minute);
            self.total_sleep += new_nap.diff;
            self.naps.push(new_nap);
        }
    }

    pub fn find_sleepiest_minute(&mut self) {
        let mut sleepiest_minute = 0;
        let mut days_asleep = 0;
        
        for minute in 0..60 {
            let cur_days_asleep = self.days_asleep_at_minute(minute);

            if days_asleep < cur_days_asleep {
                sleepiest_minute = minute;
                days_asleep = cur_days_asleep;
            }
        }
        
        self.sleepiest_minute = (sleepiest_minute, days_asleep);
    }
    
    fn days_asleep_at_minute(&self, minute: usize) -> usize {
        let mut days_asleep = 0;

        for nap in self.naps.iter() {
            if nap.is_asleep_at(minute) {
                days_asleep += 1;
            }
        }

        days_asleep
    }
}