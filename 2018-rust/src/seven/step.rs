use core::fmt::Debug;

pub struct Step {
    letter: char,
    pub children: Vec<char>,
    pub parents: Vec<char>,
    finished: bool,
}

impl Step {
    pub fn new(letter: char) -> Step {
        Step {
            letter,
            children: Vec::new(),
            parents: Vec::new(),
            finished: false,
        }
    }

    // pub fn is_ready(&self) -> bool {
    //     self.parents.is_empty() && self.finished == false
    // }

    // pub fn remove_parent(&mut self, letter: char) {
    //     self.parents = self
    //         .parents
    //         .iter()
    //         .filter(|parent| **parent == letter)
    //         .map(|parent| *parent)
    //         .collect();
    // }

    // pub fn finish(&mut self) {
    //     self.finished = true;
    // }
}

impl Debug for Step {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "step {}", self.letter)?;
        writeln!(f, "  depends on {:?}", self.parents)?;
        writeln!(f, "  dependent of {:?}", self.children)?;

        Ok(())
    }
}
