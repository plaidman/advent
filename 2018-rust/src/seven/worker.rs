pub struct Worker {
    current: char,
    remaining: u32,
    pub working: bool,
}

impl Worker {
    pub fn new() -> Worker {
        Worker {
            current: ' ',
            remaining: 0,
            working: false,
        }
    }

    pub fn increment(&mut self) -> bool {
        if !self.working {
            return false;
        }

        self.remaining -= 1;

        if self.remaining <= 0 {
            self.working = false;
            return true;
        }

        false
    }

    pub fn start_task(&mut self, letter: char, padding: u32) {
        let ord_a: u32 = 'A'.into();

        self.current = letter;
        self.remaining = &letter.into() - ord_a + padding + 1;
        self.working = true;
    }
}
