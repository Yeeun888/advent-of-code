// Day-3 Joltage

use std::{
    io::{self, BufRead},
};

// Recursive Version
// lowkey clean 
//
// s: string of numbers
// len: length of biggest number
fn largest_joltage_recursive(s: &str, len: usize) -> u128 {
    if len == 0 {
        return 0;
    }

    // Relative to string left
    let mut num: (usize, u128) = (0, 0);

    let str_len = s.chars().count();
    for (i, c) in s.chars().enumerate().take(str_len - len + 1) { 
        // First largest greedily takes the largest possible number without
        // giving up possibilities of larger ones
        if num.1 < c.to_digit(10).expect("Expected message with numbers only").into() {
            num = (i, c.to_digit(10).expect("Expected message with numbers only").into());
        }
    }

    num.1 * 10u128.pow((len - 1) as u32) + largest_joltage_recursive(&s[num.0 + 1..], len - 1)
}

fn main() {
    let stdin = io::stdin();
    let batteries: Vec<String> = stdin
        .lock()
        .lines()
        .map_while(Result::ok)
        .filter(|l| !l.is_empty())
        .collect();

    // println!("{:?}", batteries);

    // Part 1 Strategy
    // 1. greedily pick the first largest number
    // 2. find the largest number after that
    //
    // Part 2 Strategy
    // 1. Modify part 1 to pick the first largest number of all len - n first numbers

    let mut joltage = 0;
    batteries.iter().for_each(|b| {
            joltage += largest_joltage_recursive(b, 12);
        }
    );

    println!("Total joltage: {}", joltage);
}
