mod one;
mod two;
mod three;
mod four;

use std::env;
use regex_lite::Regex;

type DayFn = fn(usize, String);

fn main() {
    let days = [
        (one::run as DayFn, "one"),
        (two::run, "two"),
        (three::run, "three"),
        (four::run, "four"),
    ];
    
    let args: Vec<String> = env::args().collect();
    let arg_string = args.join(" ");
    let regex = Regex::new(r"^.* (\d+)\.([12]) (.*)$").unwrap();
    
    println!("\n");

    if !regex.is_match(&arg_string) {
        println!("usage: cargo run <day.part> <input>");
        println!("  <day> must be an integer");
        println!("  <part> must be 1 or 2");
        println!("  <input> must be a filename");
        return;
    }

    let (day, part, filename) = regex.captures(&arg_string).and_then(
        |cap| Some((
            cap.get(1).unwrap().as_str().parse::<usize>().unwrap(),
            cap.get(2).unwrap().as_str().parse::<usize>().unwrap(),
            cap.get(3).unwrap().as_str().parse::<String>().unwrap(),
        ))
    ).unwrap();

    if day > days.len() {
        println!("usage: cargo run <day.part> <input>");
        println!("  <day> cannot be greater than {}", days.len());
        return;
    }
    
    let (day_fn, folder) = days[day-1];
    let filename = format!("src/{}/{}.txt", folder, filename);
    day_fn(part, filename)
}
