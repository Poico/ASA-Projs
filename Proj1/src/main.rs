use std::collections::BinaryHeap;

fn main() {
    
    //read the X and Y of the plate that will be cut
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    let mut iter = input.split_whitespace();
    let x_plate: i32 = iter.next().unwrap().parse().unwrap(); // protects from code injection
    let y_plate: i32 = iter.next().unwrap().parse().unwrap();
    
    //read the number different ways to cut a plate
    std::io::stdin().read_line(&mut input).unwrap();
    let number_of_plates: i32 = input.trim().parse().unwrap();

    //read n values and add to the priority queue
    let mut pq_plates = BinaryHeap::new(); // create a new priority queue
    
    for _ in 0..number_of_plates {
        let mut input = String::new();
        std::io::stdin().read_line(&mut input).unwrap();
        let mut iter = input.split_whitespace();
        let x: i32 = iter.next().unwrap().parse().unwrap(); // protects from code injection
        let y: i32 = iter.next().unwrap().parse().unwrap();
        let price: i32 = iter.next().unwrap().parse().unwrap();
        let area = x * y;

        pq_plates.push((x, y, price), area/price);
    }
    
    
}
