use core::str::FromStr;
use core::fmt::Debug;
use regex_lite::Regex;

#[derive(Debug)]
pub struct EventParseError;

#[derive(PartialEq, Eq, PartialOrd, Ord)]
pub struct Event {
    month: usize,
    day: usize,
    hour: usize,
    pub minute: usize,
    pub guard_id: Option<usize>,
}

impl Event {
    pub fn get_day_stamp(&self) -> usize {
        self.month * 100 + self.day
    }
}

impl Debug for Event {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "on {}/{} at {}:{}, {:?}", self.month, self.day, self.hour, self.minute, self.guard_id)
    }
}

impl FromStr for Event {
    type Err = EventParseError;

    fn from_str(line: &str) -> Result<Self, Self::Err> {
        let line_regex = Regex::new(r"\[\d+-(\d+)-(\d+) (\d+):(\d+)] (.+)$").unwrap();
        let (month, day, hour, minute, desc) = line_regex.captures(line).and_then(
            |cap| Some((
                cap.get(1).unwrap().as_str().parse::<usize>().unwrap(),
                cap.get(2).unwrap().as_str().parse::<usize>().unwrap(),
                cap.get(3).unwrap().as_str().parse::<usize>().unwrap(),
                cap.get(4).unwrap().as_str().parse::<usize>().unwrap(),
                cap.get(5).unwrap().as_str(),
            ))
        ).ok_or(EventParseError)?;
        
        let desc_regex = Regex::new(r"Guard #(\d+) begins shift").unwrap();
        let guard_id = desc_regex.captures(desc).and_then(
            |cap| Some(cap.get(1).unwrap().as_str().parse::<usize>().unwrap())
        );

        return Ok(Event { guard_id, month, day, hour, minute });
    }
}
