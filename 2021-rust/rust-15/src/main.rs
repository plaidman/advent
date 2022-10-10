use std::{ io::{ BufReader, BufRead }, fs::File };

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
    dijkstra(0, 0, &mut path, &growth, size);
    
    println!("{:?}", path);
    println!("done");
}

fn dijkstra(row: usize, col: usize, path: &mut Vec<Vec<u32>>, growth: &Vec<Vec<u32>>, size: usize) {
    let risk = path[row][col];

    if row > 0 && path[row-1][col] > risk + growth[row-1][col] {
        path[row-1][col] = risk + growth[row-1][col];
        dijkstra(row-1, col, path, growth, size);
    }

    if col > 0 && path[row][col-1] > risk + growth[row][col-1] {
        path[row][col-1] = risk + growth[row][col-1];
        dijkstra(row, col-1, path, growth, size);
    }

    if row < size-1 && path[row+1][col] > risk + growth[row+1][col] {
        path[row+1][col] = risk + growth[row+1][col];
        dijkstra(row+1, col, path, growth, size);
    }

    if col < size-1 && path[row][col+1] > risk + growth[row][col+1] {
        path[row][col+1] = risk + growth[row][col+1];
        dijkstra(row, col+1, path, growth, size);
    }
}
