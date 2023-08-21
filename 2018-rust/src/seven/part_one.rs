use super::manual::Manual;
use regex_lite::Regex;

pub fn run(lines: Vec<String>) {
    let mut manual = Manual::new();

    for line in lines {
        let regex =
            Regex::new(r"Step ([A-Z]) must be finished before step ([A-Z]) can begin.").unwrap();
        let (parent, child) = regex
            .captures(&line)
            .and_then(|cap| {
                Some((
                    cap.get(1).unwrap().as_str().chars().next().unwrap(),
                    cap.get(2).unwrap().as_str().chars().next().unwrap(),
                ))
            })
            .unwrap();

        let parent_step = manual.get_step_mut_or_insert(parent);
        parent_step.children.push(child);

        let child_step = manual.get_step_mut_or_insert(child);
        child_step.parents.push(parent);
    }

    for step in manual.step_list {
        println!("{:?}", step);
    }
}
