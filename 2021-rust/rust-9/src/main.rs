use std::{io::{BufReader, BufRead, Error}, fs::File};

// algorithm is not mine, see notes.txt
// code is mine

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let lines = Vec::from_iter(BufReader::new(file).lines().map(parse_line));
    
    let height = lines.len();
    let width = lines[0].len();
    let mut basins = vec![];
    for x in 0..width {
        for y in 0..height {
            if is_low_point(y, x, &lines) {
                basins.push(basin_size(y, x, &lines, &mut vec![]));
            }
        }
    }
    
    basins.sort_unstable();
    basins.reverse();
    let sum = basins[0] * basins[1] * basins[2];
    
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
    if y > 0 && heightmap[y-1][x] <= heightmap[y][x] { return false }
    if x > 0 && heightmap[y][x-1] <= heightmap[y][x] { return false }
    if y < heightmap.len()-1 && heightmap[y+1][x] <= heightmap[y][x] { return false }
    if x < heightmap[y].len()-1 && heightmap[y][x+1] <= heightmap[y][x] { return false }

    return true;
}

fn basin_size(y: usize, x: usize, heightmap: &Vec<Vec<u32>>, visited: &mut Vec<(usize, usize)>) -> u32 {
    if visited.contains(&(x,y)) { return 0 }
    if heightmap[y][x] == 9 { return 0 }
    visited.push((x,y));
 
    let mut sum = 1;
    if y > 0 { sum += basin_size(y-1, x, heightmap, visited) }
    if x > 0 { sum += basin_size(y, x-1, heightmap, visited) }
    if y < heightmap.len()-1 { sum += basin_size(y+1, x, heightmap, visited) }
    if x < heightmap[y].len()-1 { sum += basin_size(y, x+1, heightmap, visited) }
    
    return sum;
}