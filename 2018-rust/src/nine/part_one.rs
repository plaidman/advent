use std::collections::VecDeque;

pub fn run(num_players: usize, num_marbles: usize) {
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
