
use std::thread;

fn main() {
    let top = 100 * 1000 * 1000;
    let mut sum: i64 = 0;

    let each = top / 10;
    let mut kids = vec![];
    for ii in 0..10 {
        kids.push(thread::spawn(|| {
            let i0 = each * ii;
            let i1 = i0 + each;

            for jj in i0..i1 {
                if jj % 101 == 0 {
                    sum = sum.wrapping_add(jj);
                }
            }
    
            println!("sum = {}", sum);
        }));
    }

    for tt in kids {
        tt.join().unwrap();
    }

    //let y = xs.iter().fold(0, |acc, x| acc + x);
    println!("sum = {}", sum);
}
