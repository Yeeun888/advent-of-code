use std::{io::{self, BufRead}, str::FromStr};

#[derive(Debug)]
struct Move {
    dir: char,
    dist: i32,
}

impl FromStr for Move {
    type Err = String;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let s = s.trim();
        
        let dir = s.chars().next().unwrap();
        let dist = s[1..].parse::<i32>()
            .map_err(|e| format!("Parse error {}", e))?;

        Ok( Move { dir: dir, dist: dist } )
    }
}

fn main() {
    let stdin = io::stdin(); 
    let moves: Vec<Move> = stdin
        .lock()
        .lines()
        .filter_map(|l| l.ok())
        .filter(|l| !l.is_empty())
        .filter_map(|l| l.parse::<Move>().ok())
        .collect();

    // println!("Parsed Moves: ");
    // moves.iter().for_each(|m| println!("{:?}", m));

    let mut pos = 50;
    let mut count = 0;
    moves.iter().for_each(|m| {
        // Part 1 logic
        // match m.dir {
        //     'L' => pos = (pos + (100 - (m.dist % 100))) % 100,
        //     'R' => pos = (pos + m.dist) % 100,
        //     _ => todo!(), 
        // };

        // if pos == 0 { 
        //     count += 1;
        // };

        // Part 2 logic instead
        count += m.dist / 100;       // See how many times it crosses into the same part
        let rem = m.dist % 100; // Remaining distance to move

        // 1. Calculate distance to 0 in the correct direction
        // 2. See if rem >= distance to 0
        // 3. if yes add 1 to count
        match m.dir {
            'L' => { count += if rem >= 100 - pos { 1 } else { 0 }; },
            'R' => { count += if rem >= pos && pos > 0 { 1 } else { 0 }; },
            _ => todo!(),
        }

        // Get new position and set it as new position
        match m.dir {
            'L' => pos = (pos + m.dist) % 100,
            'R' => pos = (pos + (100 - (m.dist % 100))) % 100,
            _ => todo!(), 
        };

        println!("move: {} {} pos: {} count: {}", m.dir, m.dist, pos, count);
    });

    println!("Final Pos: {}", pos);
    println!("Ans: {}", count);
}

// Too low: 5645
// Too high: 6142