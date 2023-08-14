pub fn run(lines: Vec<Vec<char>>) {
    let mut i = 0;
    let mut j = 1;

    let mut most_common = Vec::<char>::new();
    let mut common: Vec<char>;
    
    loop {
        loop {
            let one = lines.get(i).unwrap();
            let two = lines.get(j).unwrap();
            
            common = find_common(one, two);
            
            if common.len() > most_common.len() {
                most_common = common;
            }
            
            j += 1;

            if j >= lines.len() {
                break;
            }
        }

        i += 1;
        j = i + 1;
        
        if i+1 >= lines.len() {
            break;
        }
    }
    
    println!("common string: {:?}", most_common.into_iter().collect::<String>());
}

fn find_common(one: &Vec<char>, two: &Vec<char>) -> Vec<char> {
    let mut common = Vec::<char>::new();
    
    for i in 0..one.len() {
        let one_letter = *one.get(i).unwrap();
        let two_letter = *two.get(i).unwrap();

        if one_letter == two_letter {
            common.push(one_letter);
        }
    }
    
    common
}
