mod pixel;

use pixel::Pixel;
use std::{
    fs::File,
    io::{BufRead, BufReader},
};

const IS_TEST: bool = false;

pub fn run(_part: usize, filename: String) {
    let file = File::open(filename).expect("failed to open file");
    let pixels: Vec<Pixel> = BufReader::new(file)
        .lines()
        .map(|line| line.unwrap().parse().unwrap())
        .collect();

    // this task required some manual time tuning.
    //   for test.txt the smallest bounding box is at time 3 (obv)
    //   for input.txt the smallest bounding box is at time 10227
    let correct_time = if IS_TEST { 3 } else { 10227 };

    let (mut min_x, mut min_y) = pixels[0].xy_at_time(correct_time);
    let mut max_x = min_x;
    let mut max_y = min_y;

    for pixel in pixels.iter() {
        let (x, y) = pixel.xy_at_time(correct_time);
        min_x = min_x.min(x);
        max_x = max_x.max(x);
        min_y = min_y.min(y);
        max_y = max_y.max(y);
    }

    let width: usize = (max_x - min_x).try_into().unwrap();
    let height: usize = (max_y - min_y).try_into().unwrap();

    let mut grid: Vec<Vec<char>> = Vec::new();
    for _ in 0..=height {
        let mut row = Vec::<char>::new();

        for _ in 0..=width {
            row.push(' ');
        }

        grid.push(row);
    }

    for pixel in pixels.iter() {
        let (x, y) = pixel.xy_at_time(correct_time);

        let adj_x: usize = (x - min_x).try_into().unwrap();
        let adj_y: usize = (y - min_y).try_into().unwrap();

        grid[adj_y][adj_x] = '*';
    }

    for row in grid {
        println!("");
        for cell in row {
            print!("{}", cell);
        }
    }
}
