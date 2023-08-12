use std::collections::HashMap;

pub fn run(lines: Vec<Vec<char>>) {
    let mut num_threes = 0;
    let mut num_twos = 0;

    for line in lines {
        let letters = count_letters(line);
        let (has_two, has_three) = count_twos_threes(letters);
        
        if has_two {
            num_twos += 1;
        }

        if has_three {
            num_threes += 1;
        }
    }
    
    println!("checksum: {}", num_twos * num_threes);
}

fn count_letters(line: Vec<char>) -> HashMap<char, usize> {
    let mut letters = HashMap::<char, usize>::new();
    
    for letter in line {
        let mut count: usize = *letters.get(&letter).unwrap_or(&0);
        count += 1;
        letters.insert(letter, count);
    }
    
    letters
}

fn count_twos_threes(letters: HashMap<char, usize>) -> (bool, bool) {
    let mut has_two = false;
    let mut has_three = false;

    for letter in letters {
        let (_, count) = letter;

        if count == 2 {
            has_two = true;
        }

        if count == 3 {
            has_three = true;
        }
    }

    (has_two, has_three)
}