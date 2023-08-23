use regex_lite::Regex;
use std::collections::VecDeque;
use std::{
    fs::File,
    io::{BufRead, BufReader},
};

pub fn run(_part: usize, filename: String) {
    let file = File::open(filename).expect("failed to open file");
    let mut line = String::new();
    BufReader::new(file).read_line(&mut line).ok();

    let regex = Regex::new(r"^(\d+) players; last marble is worth (\d+) points$").unwrap();
    let (num_players, num_marbles) = regex
        .captures(&line)
        .and_then(|cap| {
            Some((
                cap[1].parse::<usize>().unwrap(),
                cap[2].parse::<usize>().unwrap(),
            ))
        })
        .unwrap();

    print!("part 1: ");
    play_game(num_players, num_marbles);
    print!("part 2: ");
    play_game(num_players, num_marbles * 100);
}

fn play_game(num_players: usize, num_marbles: usize) {
    let mut players = vec![0; num_players];
    let mut cur_player = 0;

    let mut marbles = VecDeque::<usize>::new();
    marbles.push_front(0);

    for marble in 1..=num_marbles {
        if marble % 23 == 0 {
            players[cur_player] += marble;
            marbles.rotate_right(7);
            let popped = marbles.pop_front().unwrap();
            players[cur_player] += popped;
        } else {
            marbles.rotate_left(2 % marbles.len());
            marbles.push_front(marble);
        }

        cur_player = (cur_player + 1) % num_players;
        // println!("[{}] -> {:?}", cur_player, marbles);
    }

    println!("{}", players.iter().max().unwrap());
}
