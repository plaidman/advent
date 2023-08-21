use core::fmt::Debug;

pub struct Step {
    letter: char,
    pub children: Vec<char>,
    pub parents: Vec<char>,
    started: bool,
    pub finished: bool,
}

impl Step {
    pub fn new(letter: char) -> Step {
        Step {
            letter,
            children: Vec::new(),
            parents: Vec::new(),
            started: false,
            finished: false,
        }
    }

    pub fn is_ready(&self) -> bool {
        self.parents.is_empty() && self.started == false
    }

    pub fn start(&mut self) {
        self.started = true;
    }

    pub fn finish_and_get_children(&mut self) -> Vec<char> {
        self.finished = true;
        self.children.clone()
    }

    pub fn remove_parent(&mut self, letter: char) {
        self.parents = self
            .parents
            .iter()
            .filter(|&&parent| parent != letter)
            .map(|parent| parent.clone())
            .collect();
    }
}

impl Debug for Step {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "step {}", self.letter)?;

        if self.finished {
            write!(f, " (finished)")?;
        } else if self.started {
            write!(f, " (started)")?;
        }

        writeln!(f, "\n  child of {:?}", self.parents)?;
        writeln!(f, "  parent of {:?}", self.children)?;

        Ok(())
    }
}
