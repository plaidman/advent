pub fn traverse_polymer(line: Vec<char>) -> usize {
    let mut remainder = Vec::<char>::new();

    for letter in line {
        let prev_opt = remainder.pop();

        if prev_opt.is_some() {
            let prev = prev_opt.unwrap();
            if reacts(prev, letter) {
                continue;
            }

            remainder.push(prev);
        }

        remainder.push(letter);
    }

    remainder.len()
}

fn reacts(one: char, two: char) -> bool {
    return one != two && one.to_lowercase().eq(two.to_lowercase());
}
