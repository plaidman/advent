use super::coord::Coord;

pub fn run(mut coords: Vec<Coord>) {
    // USE 32 HERE FOR TEST DATA
    let max_dist = 10000;

    // calculate bounds of grid
    let mut top = 1000;
    let mut bottom = 0;
    let mut left = 1000;
    let mut right = 0;
    for coord in coords.iter() {
        top = top.min(coord.y);
        bottom = bottom.max(coord.y);
        left = left.min(coord.x);
        right = right.max(coord.x);
    }

    // compress unused grid spaces
    for coord in coords.iter_mut() {
        coord.x = coord.x - left;
        coord.y = coord.y - top;
    }

    let mut cells_in_max_dist = 0;
    let height = bottom - top + 1;
    let width = right - left + 1;
    for x in 0..width {
        for y in 0..height {
            let mut sum_dist = 0;

            for i in 0..coords.len() {
                sum_dist += coords.get(i).unwrap().dist(x, y);
            }

            if sum_dist < max_dist {
                cells_in_max_dist += 1;
            }
        }
    }

    println!("total cells within max-dist: {}", cells_in_max_dist);
}
