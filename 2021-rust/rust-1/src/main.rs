use std::{ fs::File, io::{ BufReader, BufRead, Error } };

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let mut lines = BufReader::new(file).lines().map(parse_line);

    let mut three: Vec<i32> = vec![];
    three.push(lines.next().unwrap());
    three.push(lines.next().unwrap());
    three.push(lines.next().unwrap());
    
    let mut prev = sum(&three);
    let mut count = 0;

    for line in lines {
        three.remove(0);
        three.push(line);

        let curr = sum(&three);
        if curr > prev {
            count += 1;
        }

        prev = curr;
    }
    
    println!("{}", count);
}

fn sum(vec: &Vec<i32>) -> i32 {
    return vec.iter().sum();
}

fn parse_line(line: Result<String, Error>) -> i32 {
    return line.unwrap().parse().unwrap();
}
