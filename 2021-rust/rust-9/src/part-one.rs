use std::{io::{BufReader, BufRead, Error}, fs::File};

// algorithm is not mine, see notes.txt
// code is mine

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let lines = Vec::from_iter(BufReader::new(file).lines().map(parse_line));
    
    let height = lines.len();
    let width = lines[0].len();
    let mut sum: u32 = 0;
    for x in 0..width {
        for y in 0..height {
            if is_low_point(y, x, &lines) {
                sum += lines[y][x]+1;
            }
        }
    }
    
    println!("{:?}", sum);
    println!("done");
}

fn parse_line(line: Result<String, Error>) -> Vec<u32> {
    return Vec::from_iter(line.unwrap().chars().map(parse_cell));
}

fn parse_cell(cell: char) -> u32 {
    return cell.to_string().parse::<u32>().unwrap();
}

fn is_low_point(y: usize, x: usize, heightmap: &Vec<Vec<u32>>) -> bool {
    if y > 0 && heightmap[y-1][x] <= heightmap[y][x] { return false; }
    if x > 0 && heightmap[y][x-1] <= heightmap[y][x] { return false; }
    if y < heightmap.len()-1 && heightmap[y+1][x] <= heightmap[y][x] { return false; }
    if x < heightmap[y].len()-1 && heightmap[y][x+1] <= heightmap[y][x] { return false; }

    return true;
}