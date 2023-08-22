use super::step::Step;
use regex_lite::Regex;
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

    pub fn parse_line(&mut self, line: String) {
        let regex =
            Regex::new(r"Step ([A-Z]) must be finished before step ([A-Z]) can begin.").unwrap();
        let (parent, child) = regex
            .captures(&line)
            .and_then(|cap| {
                Some((
                    cap[1].chars().nth(0).unwrap(),
                    cap[2].chars().nth(0).unwrap(),
                ))
            })
            .unwrap();

        let parent_step = self.get_step_mut_or_insert(parent);
        parent_step.children.push(child);

        let child_step = self.get_step_mut_or_insert(child);
        child_step.parents.push(parent);
    }

    pub fn all_done(&self) -> bool {
        self.step_list
            .iter()
            .filter(|(_, step)| step.finished == false)
            .count()
            == 0
    }

    pub fn find_earliest_ready(&self) -> Option<char> {
        let item = self
            .step_list
            .iter()
            .filter(|(_, step)| step.is_ready())
            .reduce(|first, second| {
                let (first_letter, first_step) = first;
                let (second_letter, second_step) = second;

                if first_letter < second_letter {
                    (first_letter, first_step)
                } else {
                    (second_letter, second_step)
                }
            });

        if item.is_none() {
            return None;
        }

        let (letter, _step) = item.unwrap();
        Some(*letter)
    }
}
