use std::{
    io::{self, BufRead},
    str::FromStr,
};

#[derive(Debug)]
struct Id {
    first: i64,
    last: i64,
}

// Given a "first-last" create a Id struct
impl FromStr for Id {
    type Err = String;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        println!("parsing: {}", s);
        let mut parts = s.split('-');
        let id_struct = Id {
            first: parts
                .next()
                .unwrap()
                .parse::<i64>()
                .map_err(|e| format!("Parse error {e}"))?,
            last: parts
                .next()
                .unwrap()
                .parse::<i64>()
                .map_err(|e| format!("Parse error {e}"))?,
        };
        println!("prased: {} {}", id_struct.first, id_struct.last);

        return Ok(id_struct);
    }
}

// Get the number of digits in an i64
fn num_digits(n: i64) -> u32 {
    if n == 0 {
        return 1;
    }

    let n = n.abs();
    (n as f64).log10().floor() as u32 + 1
}

// Split an even-digit i64 into left and right halves
fn split_even(n: i64) -> (i64, i64) {
    let is_negative = n < 0;
    let n = n.abs();

    let digits = num_digits(n);
    let divisor = 10_i64.pow(digits / 2);

    let left = n / divisor;
    let right = n % divisor;

    let left = if is_negative { -left } else { left };

    (left, right)
}

// Get number of divisors (not including 1)
fn divisors_iter(n: i64) -> Vec<i64> {
    (2..=n).filter(|&i| n % i == 0).collect()
}

fn split_exact(s: &str, num_pieces: usize) -> Option<Vec<&str>> {
    if s.len() % num_pieces != 0 {
        return None; // Can't split evenly
    }

    let piece_size = s.len() / num_pieces;
    Some(
        (0..num_pieces)
            .map(|i| &s[i * piece_size..(i + 1) * piece_size])
            .collect(),
    )
}

// Finds if there is a repeating number
fn has_repeating(num: i64) -> bool {
    // Get divisors which divide the length of the number into equal pieces
    let divs = divisors_iter(num_digits(num) as i64);

    println!("{:?}", divs);

    let repeating = divs.iter().any(|d| {
        let u: usize = *d as usize;
        let num_str = num.to_string();
        let n = split_exact(&num_str, u).unwrap();

        println!("{:?}", n);

        n.windows(2).all(|w| w[0] == w[1])
    });

    if repeating {
        println!("detected {}", num);
    }

    repeating
}

fn main() {
    let stdin = io::stdin();
    let mut buf = String::new();

    {
        let mut handle = stdin.lock();
        let _ = handle.read_line(&mut buf);
    } // Drop stdin lock

    let ids: Vec<Id> = buf
        .trim()
        .split(',')
        .filter(|s| !s.is_empty())
        .map(|s| s.parse::<Id>().unwrap())
        .collect();

    let mut count: i128 = 0;
    ids.into_iter().for_each(|id| {
        for num in id.first..=id.last {
            // Part 1 Logic
            // if num_digits(num) % 2 == 1 {
            //     //Odd number digits are useless
            //     continue;
            // }
            //
            // let (n1, n2) = split_even(num);
            // if n1 == n2 {
            //     println!("found {} as number to add", num);
            //     count += num as i128;
            // }

            // Part 2 Logic
            if has_repeating(num) {
                count += num as i128;
            }
        }
    });

    println!("Count: {}", count);
}
