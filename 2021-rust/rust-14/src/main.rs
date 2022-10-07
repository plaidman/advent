use std::{ io::{ BufReader, BufRead }, fs::File, collections::{ VecDeque, HashMap } };

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let mut lines = VecDeque::from_iter(BufReader::new(file).lines().map(|i| i.unwrap()));
    
    let mut polymer = lines.pop_front().unwrap();
    lines.pop_front();
    let poly_pairs = parse_pairs(&lines);

    for _ in 0..10 {
        polymer = poly_step(polymer, &poly_pairs);
    }
    
    let totals = calculate_totals(&polymer);
    println!("{:?}", totals);

    println!("done");
}

fn calculate_totals(polymer: &String) -> HashMap<char, u32> {
    let mut totals = HashMap::new();
    let elems = polymer.chars();

    for elem in elems {
        *totals.entry(elem).or_insert(0) += 1;
    }
    
    return totals;
}

fn poly_step(before: String, pairs: &HashMap<String, char>) -> String {
    let mut after = "".to_string();

    for i in 0..before.len()-1 {
        let pair = before.get(i..i+2).unwrap().to_string();
        let middle = pairs.get(&pair.to_string()).unwrap();
        
        after.push(pair.chars().nth(0).unwrap());
        after.push(middle.clone());
    }
    
    after.push(before.chars().nth(before.len()-1).unwrap());
    
    return after;
}

fn parse_pairs(lines: &VecDeque<String>) -> HashMap<String, char> {
    let mut poly_pairs: HashMap<String, char> = HashMap::new();

    for i in 0..lines.len() {
        let line = Vec::from_iter(lines[i].split(" -> ").map(|i| i.to_string()));
        poly_pairs.insert(line[0].clone(), line[1].chars().nth(0).unwrap());
    }
    
    return poly_pairs;
}
