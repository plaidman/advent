use std::{io::{BufReader, BufRead}, fs::File};

const DAYS: u16 = 256;

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let mut lines = BufReader::new(file).lines().map(|i| i.unwrap());
    
    let line = lines.next().unwrap();
    let mut fish = Vec::from_iter(line.split(',').map(|i| i.parse::<u8>().unwrap()));
    let mut spawn = 0;
    
    // keep an array of the number of fish in day 0, day 1, day 2, etc.
    // cycle them toward the 0th element. when they hit the 0th element, move them to the 6th position and increment the 8th element
    
    for day in 0..DAYS {
        println!("{day}");

        for i in 0..fish.len() {
            if fish[i] == 0 {
                fish[i] = 6;
                spawn += 1;
                continue;
            }

            fish[i] -= 1;
        }
        
        for _i in 0..spawn {
            fish.push(8);
        }
        spawn = 0;
    }

    println!("{:?}", fish.len());
    println!("done");
}
