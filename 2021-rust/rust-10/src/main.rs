use std::{ io::{ BufReader, BufRead }, fs::File };

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let lines = BufReader::new(file).lines().map(|i| i.unwrap());
    
    let mut scores = vec![];
    for line in lines {
        let chars = Vec::from_iter(line.chars());
        let remainder_opt = complete_line(chars);

        if remainder_opt == None { continue }

        let mut remainder = remainder_opt.unwrap();
        remainder.reverse();

        scores.push(calculate_score(remainder));
    }
    
    scores.sort();
    println!("{:?}", scores[scores.len() / 2]);
    println!("done");
}

fn calculate_score(remainder: Vec<char>) -> u64 {
    let mut sum: u64 = 0;
    
    for char in remainder {
        sum *= 5;

        match char {
            ')' => { sum += 1 },
            ']' => { sum += 2 },
            '}' => { sum += 3 },
            '>' => { sum += 4 },
            _ => { sum += 0 },
        }
        
    }

    return sum;
}

fn complete_line(chars: Vec<char>) -> Option<Vec<char>> {
    let mut expected = vec![];

    for char in chars {
        match char {
            '(' => { expected.push(')') },
            '[' => { expected.push(']') },
            '{' => { expected.push('}') },
            '<' => { expected.push('>') },
            _ => {
                if expected.pop().unwrap() != char {
                    return None;
                }
            },
        }
    }

    return Some(expected);
}