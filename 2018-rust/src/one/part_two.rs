use std::collections::HashMap;

pub fn run(lines: Vec<String>) {
    let mut sum = 0;
    let mut tracker = HashMap::new();
    let mut current = 0;

    loop {
        sum += lines[current].parse::<i32>().unwrap();

        if tracker.contains_key(&sum) {
            break;
        }

        tracker.insert(sum, true);
        current = (current + 1) % lines.len();
    }

    println!("{} visited twice", sum);
}
