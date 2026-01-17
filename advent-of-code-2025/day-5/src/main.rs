use std::{io::{self, Read}};

fn is_in_range(ranges: &[(i64, i64)], num: i64) -> bool {
    ranges.iter().any(|(lower, upper)| {
        *lower <= num && num <= *upper 
    })
}

fn main() {
    let mut input = String::new();
    let _ = io::stdin().read_to_string(&mut input).unwrap();

    let mut sections = input.split("\n\n");

    // Parse ranges and numbers
    let ranges: Vec<(i64, i64)> = sections.next()
        .unwrap()
        .lines()
        .map(|l| {
            let mut part = l.split('-');
            let start = part.next().unwrap().parse().unwrap();
            let end = part.next().unwrap().parse().unwrap();
            (start, end)
        })
        .collect();

    let numbers: Vec<i64> = sections.next()
        .unwrap()
        .lines()
        .map(|l| {
            l.parse().unwrap()
        })
        .collect();

    // First part
    let fresh = numbers.iter()
        .filter(|n| {
            is_in_range(&ranges, **n)
        })

        .count();
    println!("Fresh: {}", fresh);

    // Second Part 
    // Based on a merging intervals problem on LC
    let mut sorted_ranges = ranges.clone();
    sorted_ranges.sort_by(|a,b| {
        a.0.cmp(&b.0)
    });
    
    let mut merged_overlaps: Vec<(i64, i64)> = Vec::new();
    for (l,r) in sorted_ranges.iter() {
        if let Some((_lm_l, lm_r)) = merged_overlaps.last_mut() && *lm_r >= *l {
            *lm_r = (*lm_r).max(*r);
            continue
        } 

        // Else we don't continue and the last merged 
        // does not overlap with the current interval
        merged_overlaps.push((*l,*r));
    }

    println!("{:?}", merged_overlaps);
    let result: i64 = merged_overlaps.iter().map(|(l,r)| {r - l + 1}).sum();
    println!("Merged overlaps are: {}", result);
}

// 313111034276413 too low
// 351974077086541 too high

// 10-13 10 11 12 13
// 14-18             14 15 16 17 18
// 12-15       12 13 14 15 
//
