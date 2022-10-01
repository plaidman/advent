use std::{io::{BufReader, BufRead}, fs::File};

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let mut lines = BufReader::new(file).lines().map(|i| i.unwrap());
    
    let line = lines.next().unwrap();
    let crabs = line.split(',').map(|i| i.parse::<usize>().unwrap());

    let mut pond: Vec<usize> = vec![];
    for crab in crabs {
        if pond.len() < crab+1 {
            pond.resize(crab+1, 0);
        }
        
        pond[crab] += 1;
    }
    
    let mut square_sums = vec![0];
    for pos in 1..pond.len() {
        square_sums.push(pos + square_sums[pos-1]);
    }
    
    let mut lowest: usize = usize::MAX;
    for pos in 0..pond.len() {
        let mut current = 0;

        for (index, count) in pond.iter().enumerate() {
            // toggle the next two lines for parts 1 and 2
            // current += index.abs_diff(pos) * count;
            current += square_sums[index.abs_diff(pos)] * count;
        }
        
        lowest = lowest.min(current);
    }
    
    println!("{:?}", lowest);
    println!("done");
}
