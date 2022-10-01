use std::{io::{BufReader, Error, BufRead}, fs::File};

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let lines = BufReader::new(file).lines().map(parse_line);

    let mut aim = 0;
    let mut x = 0;
    let mut y = 0;

    for (dir, dist) in lines {
        match dir.as_str() {
            "forward" => { x += dist; y += aim * dist }
            "up" => { aim -= dist; }
            "down" => { aim += dist; }
            &_ => {}
        }
    }
    
    println!("{}", x * y);
}

fn parse_line(line_res: Result<String, Error>) -> (String, i32) {
    let line = line_res.unwrap();
    let mut parts = line.split(' ');
    let dir = parts.next().unwrap().to_string();
    let dist = parts.next().unwrap().parse().unwrap();
    
    return (dir, dist);
}