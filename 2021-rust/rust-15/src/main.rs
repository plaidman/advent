use std::{ io::{ BufReader, BufRead }, fs::File, collections::VecDeque };

struct Cell {
    row: usize,
    col: usize,
    risk: u32,
}

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let growth = Vec::from_iter(BufReader::new(file).lines().map(
        |row| Vec::from_iter(row.unwrap().chars().map(
            |col| col.to_digit(10).unwrap()
        ))
    ));
    let size = growth.len();
    
    let row = vec![u32::MAX; size];
    let mut path = vec![row; size];
    path[0][0] = growth[0][0];
    
    let mut queue = VecDeque::new();
    queue.push_back(Cell { row: 0, col: 0, risk: growth[0][0] });
    
    while queue.len() > 0 {
        
    }

    
    
    println!("{:?}", path);
    println!("done");
}

fn print_grid(grid: &Vec<Vec<u32>>) {
    for i in 0..grid.len() {
        println!("{:?}", grid[i])
    }

    println!("");
}
