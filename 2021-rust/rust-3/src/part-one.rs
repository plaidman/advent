use std::{io::{BufReader, Error, BufRead}, fs::File};

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let lines = BufReader::new(file).lines().map(parse_line);
    
    let mut tally: Vec<i32> = vec![];
    
    for line in lines {
        tally_line(&mut tally, line);
    }
    
    let mut gamma = 0;
    let mut epsilon = 0;
    for column in tally {
        gamma *= 2;
        epsilon *= 2;

        if column < 0 {
            gamma += 1;
        } else {
            epsilon += 1;
        }
    }
    
    println!("{:?}", gamma * epsilon)
}

fn tally_line(tally: &mut Vec<i32>, line: String) {
    for (i, c) in line.chars().enumerate() {
        if tally.len() == i {
            tally.push(0);
        }
        
        match c {
            '0' => { tally[i] -= 1 }
            '1' => { tally[i] += 1 }
            _ => {}
        }
    }
}

fn parse_line(line_res: Result<String, Error>) -> String {
    return line_res.unwrap();
}