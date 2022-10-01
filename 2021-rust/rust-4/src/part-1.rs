use std::{io::{BufReader, BufRead}, fs::File};

#[derive(Debug)]
struct Square {
    num: u32,
    marked: bool,
}

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let mut lines = BufReader::new(file).lines()
        .map(|i| i.unwrap()) 
        .filter(|i| { i.len() > 0 });
    
    let draw_line = lines.next().unwrap();
    let draw_nums = draw_line.split(',').map(|i| i.parse::<u32>().unwrap());
    
    let mut board_nums: Vec<u32> = vec![];
    for line in lines {
        let mut digits = Vec::from_iter(line.split_whitespace().map(|i| i.parse::<u32>().unwrap()));
        board_nums.append(&mut digits);
    }
    let mut boards = Vec::from_iter(board_nums.chunks(25).map(parse_board));
    
    let mut win_board = 0;
    let mut win_num = 0;
    
    for draw_num in draw_nums {
        mark_board(draw_num, &mut boards);

        if let Some(winner) = check_winner(&boards) {
            win_board = winner;
            win_num = draw_num;
            break;
        }
    }
    
    println!("{:?}", sum_winner(boards.get(win_board).unwrap()) * win_num);

    println!("done");
}

fn sum_winner(board: &Vec<Square>) -> u32 {
    let mut sum = 0;

    for square in board {
        if square.marked == false {
            sum += square.num;
        }
    }
    
    return sum;
}

fn check_winner(boards: &Vec<Vec<Square>>) -> Option<usize> {
    for (board_num, board) in boards.iter().enumerate() {
        for idx in [0,5,10,15,20] {
            if check_horiz(&board, idx) {
                return Some(board_num);
            }
        }
        
        for idx in 0..5 {
            if check_vert(&board, idx) {
                return Some(board_num);
            }
        }
    }
    
    return None;
}

fn check_vert(board: &Vec<Square>, start: usize) -> bool {
    return board.iter().skip(start).step_by(5).all(|i| i.marked == true);
}

fn check_horiz(board: &Vec<Square>, start: usize) -> bool {
    return board.iter().skip(start).take(5).all(|i| i.marked == true);
}

fn mark_board(num: u32, boards: &mut Vec<Vec<Square>>) {
    for board in boards {
        for mut square in board {
            if square.num == num {
                square.marked = true;
            }
        }
    }
}

fn parse_board(nums: &[u32]) -> Vec<Square> {
    let mut squares = vec![];

    for num in nums {
        let square = Square { num: *num, marked: false };
        squares.push(square);
    }
    
    return squares;
}
