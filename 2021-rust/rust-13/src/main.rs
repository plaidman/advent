use std::{ io::{ BufReader, BufRead }, fs::File };

fn main() {
    let file = File::open("src/input.txt").expect("failed to open file");
    let lines = Vec::from_iter(BufReader::new(file).lines().map(|i| i.unwrap()));
    let sections = Vec::from_iter(lines.split(|i| i.len() == 0));

    let mut sheet = parse_sheet(parse_coords(sections[0]));

    let folds = parse_folds(sections[1]);
    for i in 0..folds.len() {
        let (horiz, pos) = folds[i];
        
        match horiz {
            true => { sheet = fold_horiz(&sheet, pos) },
            false => { sheet = fold_vert(&sheet, pos) },
        }
    }

    print_sheet(&sheet);

    println!("done");
}

fn fold_vert(sheet: &Vec<Vec<bool>>, pos: usize) -> Vec<Vec<bool>> {
    let mut new_sheet = vec![];
    
    for i in 0..sheet.len() {
        new_sheet.push(fold_row(&sheet[i], pos));
    }

    return new_sheet;
}

fn fold_row(row: &Vec<bool>, pos: usize) -> Vec<bool> {
    let mut new_row = vec![];
    
    for i in 0..pos {
        new_row.push(row[i])
    }

    let new_last_index = new_row.len() - 1;

    for i in pos+1..row.len() {
        let new_offset = i - pos - 1;
        
        if !row[i] { continue }

        new_row[new_last_index - new_offset] = true;
    }

    return new_row;
}

fn fold_horiz(sheet: &Vec<Vec<bool>>, pos: usize) -> Vec<Vec<bool>> {
    let mut new_sheet = vec![];

    for i in 0..pos {
        new_sheet.push(sheet[i].clone())
    }
    
    let new_last_index = new_sheet.len() - 1;
    
    for i in pos+1..sheet.len() {
        let source_row = &sheet[i];
        let new_offset = i - pos - 1;
        
        for j in 0..source_row.len() {
            if !source_row[j] { continue }
            
            new_sheet[new_last_index - new_offset][j] = true;
        }
    }
    
    return new_sheet;
}

fn parse_folds(input: &[String]) -> Vec<(bool, usize)> {
    let parts = Vec::from_iter(input.iter().map(
        |i| Vec::from_iter(i.get(11..i.len()).unwrap().split('='))
    ));
    
    let mut folds = vec![];
    for part in parts {
        let mut horiz = false;
        if part[0] == "y" { horiz = true }

        let pos = part[1].parse::<usize>().unwrap();

        folds.push((horiz, pos));
    }
    
    return folds;
}

fn parse_coords(input: &[String]) -> Vec<Vec<usize>> {
    return Vec::from_iter(input.iter().map(
        |i| Vec::from_iter(i.split(',').map(
            |j| j.parse::<usize>().unwrap()
        ))
    ));
}

fn parse_sheet(coords: Vec<Vec<usize>>) -> Vec<Vec<bool>> {
    let mut height: usize = 0;
    let mut width: usize = 0;
    for i in 0..coords.len() {
        let (col, row) = (coords[i][0], coords[i][1]);
        height = height.max(row);
        width = width.max(col);
    }
    
    let row: Vec<bool> = vec![false; width+1];
    let mut sheet: Vec<Vec<bool>> = vec![row; height+1];
    for i in 0..coords.len() {
        let (col, row) = (coords[i][0], coords[i][1]);
        sheet[row][col] = true;
    }

    return sheet;
}

fn print_sheet(sheet: &Vec<Vec<bool>>) {
    for row in sheet {
        for cell in row {
            match cell {
                true => { print!("#") },
                _ => { print!(".") },
            }
        }
        
        println!("");
    }
    
    println!("");
}
