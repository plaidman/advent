use std::{io::{BufReader, Error, BufRead}, fs::File};

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let lines = BufReader::new(file).lines().map(parse_line);
    
    let mut curr: Vec<Vec<u32>> = Vec::from_iter(lines);
    let mut idx = 0;
    
    while curr.len() > 1 {
        curr = separate(curr, idx);
        idx += 1;
    }
    
    println!("{:?}", convert(curr.first().unwrap().to_vec()));
}

fn separate(lines: Vec<Vec<u32>>, idx: usize) -> Vec<Vec<u32>> {
    let mut one = vec![];
    let mut zero = vec![];

    for line in lines {
        if line[idx] == 1 {
            one.push(line);
        } else {
            zero.push(line);
        }
    }
    
    // >= for oxygen
    // < for co2 scrubber
    if one.len() < zero.len() {
        return one;
    } else {
        return zero;
    }
}

fn convert(v: Vec<u32>) -> u32 {
    let mut total = 0;
    
    for digit in v {
        total *= 2;
        total += digit;
    }
    
    return total;
}

fn parse_line(line_res: Result<String, Error>) -> Vec<u32> {
    let line = line_res.unwrap();
    return Vec::from_iter(line.chars().map(parse_char));
}

fn parse_char(c: char) -> u32 {
    return c.to_digit(10).unwrap();
}