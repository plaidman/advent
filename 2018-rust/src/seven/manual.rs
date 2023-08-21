use super::step::Step;
use std::collections::HashMap;

pub struct Manual {
    pub step_list: HashMap<char, Step>,
}

impl Manual {
    pub fn new() -> Manual {
        Manual {
            step_list: HashMap::new(),
        }
    }

    pub fn get_step_mut_or_insert(&mut self, letter: char) -> &mut Step {
        self.step_list.entry(letter).or_insert(Step::new(letter))
    }
}
