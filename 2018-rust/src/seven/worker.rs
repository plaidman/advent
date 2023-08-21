use super::manual::Manual;

pub struct Worker {
    pub current: char,
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

    pub fn pick_up_new_task(&mut self, manual: &mut Manual, step_padding: u32) {
        if self.working {
            return;
        }

        let ready_step_opt = manual.find_earliest_ready();
        if ready_step_opt == None {
            return;
        }

        let ready_step_letter = ready_step_opt.unwrap();
        let ready_step = manual.get_step_mut_or_insert(ready_step_letter);

        ready_step.start();
        self.start_task(ready_step_letter, step_padding);

        println!("  worker picked up task {}", ready_step_letter);
    }
}
