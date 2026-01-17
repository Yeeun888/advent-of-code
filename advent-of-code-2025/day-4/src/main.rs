use std::{io::{self, BufRead}};

fn two_dimensional_vector_get<T>(vec: &[Vec<T>], row: usize, col: usize) -> Option<&T> {
    let v = vec.get(row)?;
    let t = v.get(col)?;

    Some(t)
}

fn check_adjacent_less_than(vec: &[Vec<char>], n: usize) -> u32 {
    let mut forklift_accessible = 0;

    for (i, v) in vec.iter().enumerate() {   // Row
        for (j, c) in v.iter().enumerate() {     // Column
            // Check all
            // TL, TM, TR 
            // ML, XX, MR
            // BL, BM, BR

            if *c != '@' {
                continue
            }

            // println!("on {},{}", i, j);

            let offsets: [(isize, isize); 8] = [
                (-1, -1), (-1,0), (-1, 1),
                (0, -1),          (0, 1),
                (1, -1),  (1,0),  (1, 1),
            ]; 

            let adjacent_at = 
                offsets.iter()
                .filter_map(|(c,r)| {
                    let row = i.checked_add_signed(*c)?;
                    let col = j.checked_add_signed(*r)?;
                    two_dimensional_vector_get(vec, row, col)
                })
                .filter(|c| **c == '@')
                .count();

            // println!("counted adjacent: {}", adjacent_at);
            if adjacent_at < n {
                // println!("yes!");
                forklift_accessible += 1;
            }
        }
    }  

    forklift_accessible
}

fn remove_adjacent_less_than(vec: &mut [Vec<char>], n: usize) -> u32 {
    let mut forklift_accessible = 0;

    let mut to_remove = Vec::new();

    for (i, v) in vec.iter().enumerate() {   // Row
        for (j, c) in v.iter().enumerate() {     // Column
            // Check all
            // TL, TM, TR 
            // ML, XX, MR
            // BL, BM, BR

            if *c != '@' {
                continue
            }

            let offsets: [(isize, isize); 8] = [
                (-1, -1), (-1,0), (-1, 1),
                (0, -1),          (0, 1),
                (1, -1),  (1,0),  (1, 1),
            ]; 

            let adjacent_at = 
                offsets.iter()
                .filter_map(|(c,r)| {
                    let row = i.checked_add_signed(*c)?;
                    let col = j.checked_add_signed(*r)?;
                    two_dimensional_vector_get(vec, row, col)
                })
                .filter(|c| **c == '@')
                .count();

            if adjacent_at < n {
                forklift_accessible += 1;
                to_remove.push((i,j));
            }
        }
    }  

    for (i, j) in to_remove {
        vec[i][j] = '.';
    }

    forklift_accessible
}

fn main() {
    let stdin = io::stdin();
    let mut char: Vec<Vec<char>> = stdin
        .lock()
        .lines()
        .map_while(Result::ok)
        .filter(|l| !l.is_empty())
        .map(|s| s.chars().collect())
        .collect();

    println!("Forklift accesible: {}", check_adjacent_less_than(&char, 4));

    let mut total_removed = 0;
    loop {
        let removed = remove_adjacent_less_than(&mut char, 4); 
        if removed == 0 {
            break;
        }

        total_removed += removed;
    }

    println!("Maximum Removable: {}", total_removed);
}
