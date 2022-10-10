use std::{ io::{ BufReader, BufRead }, fs::File, collections::{ VecDeque, HashMap } };

// algorithm is not mine but the code is mine

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let mut lines = VecDeque::from_iter(BufReader::new(file).lines().map(|i| i.unwrap()));
    
    let mut polymer_str = lines.pop_front().unwrap();
    let mut polymer = parse_polymer(polymer_str.clone());
    // remember the last character of the initial string for counting later
    let last_char = polymer_str.pop().unwrap();

    lines.pop_front(); // discard blank line
    
    // calculate the before and after state of the remaining lines
    let poly_pairs = parse_pairs(&lines);

    // change this to 10 for part-one
    for _ in 0..40 {
        polymer = poly_step(polymer, &poly_pairs);
    }

    let totals = calculate_totals(polymer, last_char);
    
    let mut max = 0;
    let mut min = u64::MAX;
    for (_key, total) in totals {
        min = min.min(total);
        max = max.max(total);
    }
    println!("{}", max - min);

    println!("done");
}

// counting totals, look at each pair. the first letter will get the sum (because the 2nd letter will be the first letter of a different pair)
// add a single point onto last_char (because that will never be the first char in a pair)
fn calculate_totals(polymer: HashMap<String, u64>, last_char: char) -> HashMap<char, u64> {
    let mut totals = HashMap::new();
    
    for (key, count) in polymer {
        let element = key.chars().next().unwrap();

        *totals.entry(element).or_insert(0) += count;
    }
    
    *totals.entry(last_char).or_insert(0) += 1;
    
    return totals;
}

// iterate by subtracting from the before state and adding to both new pairs in the after state
fn poly_step(before: HashMap<String, u64>, pairs: &HashMap<String, Vec<String>>) -> HashMap<String, u64> {
    let mut after = HashMap::new();

    for (key, count) in before {
        for new_pair in pairs.get(&key).unwrap() {
            *after.entry(new_pair.clone()).or_insert(0) += count;
        }
    }
    
    return after;
}

// start with the count of pairs from the initial template string
fn parse_polymer(polymer_line: String) -> HashMap<String, u64> {
    let mut poly_pairs = HashMap::new();
    let chars = Vec::from_iter(polymer_line.chars());

    for i in 0..chars.len()-1 {
        let key = format!("{}{}", chars[i], chars[i+1]);

        *poly_pairs.entry(key).or_insert(0) += 1;
    }
    
    return poly_pairs;
}

// keep track of each origin pair (before state),
// and a Vec of the two resulting pairs (after state)
fn parse_pairs(lines: &VecDeque<String>) -> HashMap<String, Vec<String>> {
    let mut poly_pairs = HashMap::new();

    for i in 0..lines.len() {
        let line = Vec::from_iter(lines[i].chars().filter(|i| i <= &'Z' && i > &'A'));
        
        let key: String = format!("{}{}", line[0], line[1]);
        let value: Vec<String> = vec![
            format!("{}{}", line[0], line[2]),
            format!("{}{}", line[2], line[1]),
        ];

        poly_pairs.insert(key, value);
    }
    
    return poly_pairs;
}
