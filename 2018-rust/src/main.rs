mod one;
mod two;
mod three;

use std::env;
use regex_lite::Regex;

type DayFn = fn(usize, String);

fn main() {
    let days = [
        (one::run as DayFn, "one"),
        (two::run, "two"),
        (three::run, "three"),
    ];
    
    let args: Vec<String> = env::args().collect();
    let arg_string = args.join(" ");
    let regex = Regex::new(r"^.* (\d+)\.([12]) (.*)").unwrap();
    
    println!("\n");

    if !regex.is_match(&arg_string) {
        println!("usage: cargo run <day.part> <input>");
        println!("  <day> must be an integer");
        println!("  <part> must be 1 or 2");
        println!("  <input> must be a filename");
        return;
    }

    let matches = regex.captures(&arg_string).unwrap();
    let day = matches.get(1).unwrap().as_str().parse::<usize>().unwrap();
    let part = matches.get(2).unwrap().as_str().parse::<usize>().unwrap();
    let filename = matches.get(3).unwrap().as_str();

    if day > days.len() {
        println!("usage: cargo run <day.part> <input>");
        println!("  <day> cannot be greater than {}", days.len());
        return;
    }
    
    let (day_fn, folder) = days[day-1];
    let filename = format!("src/{}/{}.txt", folder, filename);
    day_fn(part, filename)
}
