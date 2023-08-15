use core::fmt::Debug;

pub struct Nap {
    start_min: usize,
    end_min: usize,
    pub diff: usize,
}

impl Debug for Nap {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{} mins from {} to {}", self.diff, self.start_min, self.end_min)
    }
}

impl Nap {
    pub fn new(start_min: usize, end_min: usize) -> Nap {
        Nap { start_min, end_min, diff: end_min - start_min }
    }
    
    pub fn is_asleep_at(&self, minute: usize) -> bool {
        return minute >= self.start_min && minute < self.end_min;
    }
}