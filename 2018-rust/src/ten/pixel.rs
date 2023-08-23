use core::str::FromStr;
use regex_lite::Regex;

pub struct Pixel {
    x: i32,
    y: i32,
    dx: i32,
    dy: i32,
}

#[derive(Debug)]
pub struct PixelParseError;

impl Pixel {
    pub fn xy_at_time(&self, time: i32) -> (i32, i32) {
        (self.x + (self.dx * time), self.y + (self.dy * time))
    }
}

impl FromStr for Pixel {
    type Err = PixelParseError;

    fn from_str(line: &str) -> Result<Self, Self::Err> {
        let line_regex =
            Regex::new(r"^position=< ?(-?\d+),  ?(-?\d+)> velocity=< ?(-?\d+),  ?(-?\d+)>$")
                .unwrap();
        let (x, y, dx, dy) = line_regex
            .captures(line)
            .and_then(|cap| {
                Some((
                    cap[1].parse::<i32>().unwrap(),
                    cap[2].parse::<i32>().unwrap(),
                    cap[3].parse::<i32>().unwrap(),
                    cap[4].parse::<i32>().unwrap(),
                ))
            })
            .ok_or(PixelParseError)?;

        Ok(Pixel { x, y, dx, dy })
    }
}
