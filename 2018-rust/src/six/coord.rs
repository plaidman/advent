use core::fmt::Debug;
use core::str::FromStr;
use regex_lite::Regex;

#[derive(Debug)]
pub struct CoordParseError;

pub struct Coord {
    pub x: usize,
    pub y: usize,
    pub area: usize,
    pub is_edge: bool,
}

impl Coord {
    pub fn dist(&self, x: usize, y: usize) -> usize {
        self.x.abs_diff(x) + self.y.abs_diff(y)
    }
}

impl Debug for Coord {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "{},{} - area: {}, is edge: {}",
            self.x, self.y, self.area, self.is_edge
        )
    }
}

impl FromStr for Coord {
    type Err = CoordParseError;

    fn from_str(line: &str) -> Result<Self, Self::Err> {
        let regex = Regex::new(r"^(\d+), (\d+)$").unwrap();
        let (x, y) = regex
            .captures(line)
            .and_then(|cap| {
                Some((
                    cap.get(1).unwrap().as_str().parse::<usize>().unwrap(),
                    cap.get(2).unwrap().as_str().parse::<usize>().unwrap(),
                ))
            })
            .ok_or(CoordParseError)?;

        return Ok(Coord {
            x,
            y,
            area: 0,
            is_edge: false,
        });
    }
}
