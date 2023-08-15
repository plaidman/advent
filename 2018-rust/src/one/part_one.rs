pub fn run(lines: Vec<String>) {
    let mut sum = 0;

    for line in lines {
        let num = line.parse::<i32>().unwrap();
        sum += num;
    }

    println!("sum: {}", sum);
}
