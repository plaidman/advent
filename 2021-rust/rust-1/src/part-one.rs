use std::{ fs::File, io::{ BufRead, BufReader, Error } };

fn main() {
    let file = File::open("src/input.txt").unwrap();
    let mut lines = BufReader::new(file).lines().map(parse_line);

    let mut count = 0;
    let mut prev: i32 = lines.next().unwrap();

    for line in lines {
        if prev < line {
            count += 1;
        }

        prev = line;
    }

    println!("{count}");
}

fn parse_line(line: Result<String, Error>) -> i32 {
    return line.unwrap().parse().unwrap();
}
