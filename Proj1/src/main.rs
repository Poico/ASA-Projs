
fn main() {
    //read two integers
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    let mut iter = input.split_whitespace();
    let _x: i32 = iter.next().unwrap().parse().unwrap();
    let _y: i32 = iter.next().unwrap().parse().unwrap();
    
}
