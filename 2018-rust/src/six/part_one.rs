use super::coord::Coord;

pub fn run(mut coords: Vec<Coord>) {
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

    // adjust coords to make grid smaller
    for coord in coords.iter_mut() {
        coord.x -= left;
        coord.y -= top;
    }

    // count grid spaces that are closest to coordinates
    let height = bottom - top + 1;
    let width = right - left + 1;
    for x in 0..width {
        for y in 0..height {
            let index = find_closest_index(x, y, &coords);

            if index.is_none() {
                continue;
            }

            let coord = coords.get_mut(index.unwrap()).unwrap();
            coord.area += 1;

            if x == 0 || y == 0 || x == width - 1 || y == height - 1 {
                coord.is_edge = true;
            }
        }
    }

    let largest: &Coord = coords
        .iter()
        .filter(|c| c.is_edge == false)
        .reduce(|x, y| if x.area > y.area { x } else { y })
        .unwrap();
    println!("largest non-infinite area: {:#?}", largest.area);
}

fn find_closest_index(x: usize, y: usize, coords: &Vec<Coord>) -> Option<usize> {
    let mut closest = 0;
    let mut dist = 999999;
    let mut is_tied = false;

    for i in 0..coords.len() {
        let cur_dist = coords[i].dist(x, y);

        if cur_dist == dist {
            is_tied = true;
        }

        if cur_dist < dist {
            dist = cur_dist;
            closest = i;
            is_tied = false;
        }
    }

    if is_tied {
        return None;
    }

    Some(closest)
}
