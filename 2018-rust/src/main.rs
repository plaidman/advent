mod eight;
mod five;
mod four;
mod nine;
mod one;
mod seven;
mod six;
mod three;
mod two;

use regex_lite::Regex;
use std::env;

type DayFn = fn(usize, String);

fn main() {
    let days = [
        (one::run as DayFn, "one"),
        (two::run, "two"),
        (three::run, "three"),
        (four::run, "four"),
        (five::run, "five"),
        (six::run, "six"),
        (seven::run, "seven"),
        (eight::run, "eight"),
        (nine::run, "nine"),
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

    let (day, part, filename) = regex
        .captures(&arg_string)
        .and_then(|cap| {
            Some((
                cap[1].parse::<usize>().unwrap(),
                cap[2].parse::<usize>().unwrap(),
                cap[3].parse::<String>().unwrap(),
            ))
        })
        .unwrap();

    if day > days.len() {
        println!("usage: cargo run <day.part> <input>");
        println!("  <day> cannot be greater than {}", days.len());
        return;
    }

    let (day_fn, folder) = days[day - 1];
    let filename = format!("src/{}/{}.txt", folder, filename);
    day_fn(part, filename)
}
