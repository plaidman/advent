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

    pub fn is_ready(&self) -> bool {
        self.parents.is_empty() && self.finished == false
    }

    pub fn remove_parent(&mut self, letter: char) {
        self.parents = self
            .parents
            .iter()
            .filter(|&&parent| parent != letter)
            .map(|parent| parent.clone())
            .collect();
    }

    pub fn complete_step_and_get_children(&mut self) -> Vec<char> {
        self.finished = true;
        self.children.iter().map(|i| i.clone()).collect()
    }
}

impl Debug for Step {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "step {}", self.letter)?;

        if self.finished {
            write!(f, " (finished)")?;
        }

        writeln!(f, "\n  depends on {:?}", self.parents)?;
        writeln!(f, "  dependent of {:?}", self.children)?;

        Ok(())
    }
}
