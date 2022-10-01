pub struct Segment {
    x: usize,
    y: usize,
    x2: usize,
    y2: usize,
    done: bool,
}

impl Segment {
    pub fn new(x: usize, y: usize, x2: usize, y2: usize) -> Segment {
        return Segment { x, y, x2, y2, done: false };
    }
    
    pub fn is_diagonal(&self) -> bool {
        return self.x != self.x2 && self.y != self.y2;
    }
}

fn step(i: usize, j: usize) -> usize {
    if i < j { return i+1; }
    if i > j { return i-1; }
    return i;
}

impl Iterator for Segment {
    type Item = (usize, usize);

    fn next(&mut self) -> Option<Self::Item> {
        if self.done {
            return None;
        }

        let val = (self.x, self.y);

        if self.x == self.x2 && self.y == self.y2 {
            self.done = true;
            return Some(val);
        }
        
        self.x = step(self.x, self.x2);
        self.y = step(self.y, self.y2);
        return Some(val);
    }
}
