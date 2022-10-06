mod octopus;

use std::{ io::{ BufReader, BufRead }, fs::File };
use octopus::{ Octopus, cooldown, print_grid, increase_power };

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let grid = &mut Vec::from_iter(BufReader::new(file).lines().map(
        |line| Vec::from_iter(line.unwrap().chars().map(
            |digit| Octopus::new(digit.to_string().parse().unwrap())
        ))
    ));
    
    let mut total = 0;

    for _ in 0..100 {
        increase_power(grid);
        total += cooldown(grid);
    }

    print_grid(grid);
    println!("{}", total);
    println!("done");
}