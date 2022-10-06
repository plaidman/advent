mod cave;

use std::{ io::{ BufReader, BufRead }, fs::File, collections::HashMap };
use cave::Cave;

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let paths = BufReader::new(file).lines().map(|i| i.unwrap());
    
    let mut map: HashMap<String, Cave> = HashMap::new();
    for path in paths {
        generate_map(path, &mut map);
    }
    
    let sum = traverse_caves("start".to_string(), &map, vec![]);
    println!("{}", sum);

    println!("done");
}

fn traverse_caves(label: String, map: &HashMap<String, Cave>, mut path: Vec<String>) -> u32 {
    if label == "end" {
        return 1;
    }
    
    let cave = map.get(&label).unwrap();
    if !cave.is_large && path.contains(&label) {
        return 0;
    }
    
    path.push(label);
    
    let mut sum = 0;
    for branch in cave.paths.as_slice() {
        sum += traverse_caves(branch.to_string(), &map, path.clone());
    }

    return sum;
}

fn generate_map(path: String, map: &mut HashMap<String, Cave>) {
    let (left, right) = path.split_once('-').unwrap();
    
    if !map.contains_key(&left.to_string()) {
        map.insert(left.to_string(), Cave::new(left.to_string()));
    }

    if !map.contains_key(&right.to_string()) {
        map.insert(right.to_string(), Cave::new(right.to_string()));
    }
    
    let left_cave = map.get_mut(&left.to_string()).unwrap();
    left_cave.paths.push(right.to_string());

    let right_cave = map.get_mut(&right.to_string()).unwrap();
    right_cave.paths.push(left.to_string());
    
    return;
}
