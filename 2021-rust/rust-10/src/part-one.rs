use std::{ io::{ BufReader, BufRead }, fs::File };

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let lines = BufReader::new(file).lines().map(|i| i.unwrap());
    
    let mut sum = 0;
    for line in lines {
        let chars = Vec::from_iter(line.chars());
        let mismatch = find_mismatch(chars);
        sum += mismatch_score(mismatch);
    }
    
    println!("{:?}", sum);
    println!("done");
}

fn mismatch_score(mismatch: char) -> u32 {
    match mismatch {
        ')' => { return 3 },
        ']' => { return 57 },
        '}' => { return 1197 },
        '>' => { return 25137 },
        _ => { return 0 },
    }
}

fn find_mismatch(chars: Vec<char>) -> char {
    let mut mismatch = ' ';
    let mut expected = vec![];

    for char in chars {
        match char {
            '(' => { expected.push(')') },
            '[' => { expected.push(']') },
            '{' => { expected.push('}') },
            '<' => { expected.push('>') },
            _ => {
                if expected.pop().unwrap() != char {
                    mismatch = char;
                    break;
                }
            },
        }
    }

    return mismatch;
}