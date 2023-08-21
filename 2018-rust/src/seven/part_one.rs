use super::manual::Manual;
pub fn run(lines: Vec<String>) {
    let mut manual = Manual::new();
    let mut letters = Vec::<char>::new();

    for line in lines {
        manual.parse_line(line);
    }

    loop {
        // for (_, step) in manual.step_list.iter() {
        //     println!("{:?}", step);
        // }

        let letter_opt = manual.find_earliest_ready();

        if letter_opt == None {
            break;
        }

        let letter = letter_opt.unwrap();
        letters.push(letter);
        let children = manual.complete_step_and_get_children(letter);

        for child in children {
            let step = manual.get_step_mut_or_insert(child);
            step.remove_parent(letter);
        }
    }

    println!("{}", letters.iter().collect::<String>());
}
