use std::{io::{BufReader, BufRead}, fs::File, collections::HashMap};

// algorithm is not mine, see notes.txt
// code is mine

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let lines = BufReader::new(file).lines().map(|i| i.unwrap());
    
    let digit_lookup = HashMap::from_iter([
        (42,0),(17,1),(34,2),(39,3),(30,4),
        (37,5),(41,6),(25,7),(49,8),(45,9)
    ]);
    
    let mut sum = 0;
    for line in lines {
        let (left, right) = line.split_once(" | ").unwrap();

        let segments = parse_segments(left);

        let digits = right.split_whitespace();
        let mut number = 0;
        for digit in digits {
            number *= 10;
            number += parse_digit(&segments, digit, &digit_lookup);
        }
        
        sum += number;
    }
    
    println!("{:?}", sum);
    println!("done");
}

fn parse_digit(segments: &HashMap<char, usize>, digit: &str, lookup: &HashMap<usize, usize>) -> usize {
    let mut sum = 0;

    let digit_iter = digit.chars();
    for digit in digit_iter {
        sum += segments.get(&digit).unwrap();
    }
    
    return *lookup.get(&sum).unwrap();
}

fn parse_segments(left: &str) -> HashMap<char, usize> {
    let mut hash = HashMap::new();
    
    let segments = left.chars();
    for segment in segments {
        if segment == ' ' { continue }
        
        let prev = hash.get(&segment);
        match prev {
            None => { hash.insert(segment, 1); }
            Some(prev) => { hash.insert(segment, prev + 1); }
        }
    }

    return hash;
}

