
pub struct Octopus {
    energy: u16,
    flashed: bool,
}

impl Octopus {
    pub fn new(energy: u16) -> Octopus {
        return Octopus { energy, flashed: false };
    }
    
    pub fn increment(&mut self) -> bool {
        if self.flashed { return false }

        self.energy += 1;
        if self.energy > 9 {
            self.flashed = true;
            return true;
        }

        return false;
    }
    
    pub fn cooldown(&mut self) -> bool {
        if self.energy <= 9 { return false }
        
        self.energy = 0;
        self.flashed = false;
        return true;
    }
}

pub fn cooldown(grid: &mut Vec<Vec<Octopus>>) -> u32 {
    let mut total = 0;

    for row in 0..10 {
        for col in 0..10 {
            if grid[row][col].cooldown() {
                total += 1;
            }
        }
    }
    
    return total;
}

pub fn increase_power(grid: &mut Vec<Vec<Octopus>>) {
    for row in 0..10 {
        for col in 0..10 {
            if grid[row][col].increment() {
                flash_neighbors(
                    isize::try_from(row).unwrap(),
                    isize::try_from(col).unwrap(),
                    grid,
                );
            }
        }
    }
}

fn flash_neighbors(flash_row: isize, flash_col: isize, grid: &mut Vec<Vec<Octopus>>) {
    let prev_row = usize::try_from((flash_row-1).clamp(0,9)).unwrap();
    let next_row = usize::try_from((flash_row+1).clamp(0,9)).unwrap();
    let prev_col = usize::try_from((flash_col-1).clamp(0,9)).unwrap();
    let next_col = usize::try_from((flash_col+1).clamp(0,9)).unwrap();
    
    for row in prev_row..=next_row {
        for col in prev_col..=next_col {
            if grid[row][col].increment() {
                flash_neighbors(
                    isize::try_from(row).unwrap(),
                    isize::try_from(col).unwrap(),
                    grid,
                );
            }
        }
    }
}

pub fn print_grid(grid: &Vec<Vec<Octopus>>) {
    for line in grid {
        for cell in line {
            if cell.flashed { print!("*") }
            else { print!("{}", cell.energy) }
        }

        println!("");
    }

    println!("");
}
