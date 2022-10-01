use std::{io::{BufReader, BufRead}, fs::File};

#[derive(Debug)]
struct Segment {
    x1: usize,
    y1: usize,
    x2: usize,
    y2: usize,
}

const SIZE: usize = 10;

fn main() {
    let file = File::open("src/test-input.txt").expect("failed to open file");
    let lines = BufReader::new(file).lines()
        .map(|i| i.unwrap())
        .map(parse_segments);
    
    let mut grid = [[0;SIZE];SIZE];
    for line in lines {
        if line.x1 != line.x2 && line.y1 != line.y2 {
            continue;
        }
        
        for x in line.x1.min(line.x2)..=line.x1.max(line.x2) {
            for y in line.y1.min(line.y2)..=line.y1.max(line.y2) {
                grid[x][y] += 1;
            }
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
    
    return Segment {
        x1: coords.next().unwrap(),
        y1: coords.next().unwrap(),
        x2: coords.next().unwrap(),
        y2: coords.next().unwrap(),
    };
}