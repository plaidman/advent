use super::manual::Manual;
pub fn run(lines: Vec<String>) {
    let mut manual = Manual::new();
    let mut letters = Vec::<char>::new();

    for line in lines {
        manual.parse_line(line);
    }

    loop {
        if manual.all_done() {
            break;
        }

        let letter = manual.find_earliest_ready().unwrap();
        letters.push(letter);

        let step = manual.get_step_mut_or_insert(letter);
        step.start();
        let children = step.finish_and_get_children();

        for child in children {
            let child_step = manual.get_step_mut_or_insert(child);
            child_step.remove_parent(letter);
        }
    }

    println!("{}", letters.iter().collect::<String>());
}
