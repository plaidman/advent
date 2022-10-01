use std::{io::{BufReader, BufRead}, fs::File};

// switch this for part 1 and 2
const DAYS: u16 = 256;

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let mut lines = BufReader::new(file).lines().map(|i| i.unwrap());
    
    let line = lines.next().unwrap();
    let fishes = line.split(',').map(|i| i.parse::<usize>().unwrap());

    let mut pond: Vec<usize> = vec![0;9];
    let mut sum = 0;
    let mut spawn;

    for fish in fishes {
        pond[fish] += 1;
        sum += 1;
    }
    
    for _day in 0..DAYS {
        spawn = pond[0];
        pond[0] = pond[1];
        pond[1] = pond[2];
        pond[2] = pond[3];
        pond[3] = pond[4];
        pond[4] = pond[5];
        pond[5] = pond[6];
        pond[6] = pond[7];
        pond[7] = pond[8];
        pond[8] = spawn;
        pond[6] += spawn;
        sum += spawn;
    }

    println!("{:?}", sum);
    println!("done");
}
