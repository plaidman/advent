use regex_lite::Regex;
use std::collections::HashMap;
use std::{
    fs::File,
    io::{BufRead, BufReader},
};

type Patch = (isize, usize, usize, usize, usize);

pub fn run(_part: usize, filename: String) {
    let file = File::open(filename).expect("failed to open file");
    let lines: Vec<String> = BufReader::new(file)
        .lines()
        .map(|line| line.unwrap())
        .collect();

    let mut fabric = HashMap::<String, isize>::new();
    let mut overlapping = HashMap::<isize, bool>::new();

    for line in lines {
        let (id, left, top, width, height) = parse_patch(line);

        overlapping.insert(id, false);

        for x in left..left + width {
            for y in top..top + height {
                let coord = coord_stringify(x, y);

                if fabric.contains_key(&coord) {
                    let other_id = *fabric.get(&coord).unwrap();

                    overlapping.insert(id, true);
                    overlapping.insert(other_id, true);

                    fabric.insert(coord, -1);
                } else {
                    fabric.insert(coord, id);
                }
            }
        }
    }

    let thing: Vec<_> = fabric
        .iter()
        .filter(|&cell| {
            let (_, id) = cell;
            *id < 0
        })
        .collect();
    println!("overlapped squares: {}", thing.len());

    let (id, _) = overlapping
        .iter()
        .find(|&fabric| {
            let (_, is_over) = fabric;
            *is_over == false
        })
        .unwrap();
    println!("unoverlapped patch id: {}", id);
}

fn coord_stringify(x: usize, y: usize) -> String {
    let mut coord = String::new();

    coord.push_str(x.to_string().as_str());
    coord.push(',');
    coord.push_str(y.to_string().as_str());

    coord
}

fn parse_patch(line: String) -> Patch {
    let regex = Regex::new(r"^#(\d+) @ (\d+),(\d+): (\d+)x(\d+)$").unwrap();

    regex
        .captures(line.as_str())
        .and_then(|cap| {
            Some((
                cap.get(1).unwrap().as_str().parse::<isize>().unwrap(),
                cap.get(2).unwrap().as_str().parse::<usize>().unwrap(),
                cap.get(3).unwrap().as_str().parse::<usize>().unwrap(),
                cap.get(4).unwrap().as_str().parse::<usize>().unwrap(),
                cap.get(5).unwrap().as_str().parse::<usize>().unwrap(),
            ))
        })
        .unwrap()
}
