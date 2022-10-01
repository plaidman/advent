mod segment;

use std::{io::{BufReader, BufRead}, fs::File};
use segment::Segment;

const SIZE: usize = 1000;

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let lines = BufReader::new(file).lines()
        .map(|i| i.unwrap())
        .map(parse_segments);
    
    let mut line = vec![];
    line.resize(SIZE, 0);
    let mut grid = vec![];
    grid.resize(SIZE, line);
    for line in lines {
        // uncomment this line for part 1
        // if line.is_diagonal() {
        //     continue;
        // }
        
        for (x,y) in line {
            grid[x][y] += 1;
        }
    }

    let mut total = 0;
    for line in grid {
        for cell in line {
            if cell >= 2 {
                total += 1;
            }
        }
    }

    println!("{:?}", total);
    println!("done");
}

fn parse_segments(line: String) -> Segment {
    let iter = line.split(" -> ");
    let mut vec = Vec::from_iter(iter);
    vec.insert(1, ",");
    let coord_str = vec.concat();
    let mut coords = coord_str.split(',').map(|i| i.parse::<usize>().unwrap());
    
    return Segment::new(
        coords.next().unwrap(),
        coords.next().unwrap(),
        coords.next().unwrap(),
        coords.next().unwrap(),
    );
}