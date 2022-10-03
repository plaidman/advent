use std::{io::{BufReader, BufRead}, fs::File};

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let lines = BufReader::new(file).lines().map(|i| i.unwrap());
    
    let mut sum = 0;
    for line in lines {
        let (_left, right) = line.split_once(" | ").unwrap();
        let digits = right.split_whitespace();
        
        for digit in digits {
            if digit.len() == 2 || digit.len() == 3 || digit.len() == 4 || digit.len() == 7 {
                sum += 1;
            }
        }
    }
    
    println!("{:?}", sum);
    println!("done");
}
