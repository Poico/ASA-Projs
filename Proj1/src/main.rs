use core::num;
use std::collections::VecDeque;
struct Retangulo {
    x: i32,
    y: i32,
    price: i32,
}

impl Retangulo {
    fn new(x: i32, y: i32, price: i32) -> Retangulo {
        Retangulo {
            x,
            y,
            price,
        }
    }
    //TODO: implement rotation <- verify if it is necessary
    fn how_many_can_fit(mut self , retangulo: &Retangulo) -> i32 {
        let x = retangulo.x / self.x;
        let y = retangulo.y / self.y;
        if x > y {
            self.price = retangulo.price*x;
            return x;
        }
        return y;
    }
}

fn main() {
    
    //read the X and Y of the plate that will be cut
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    let mut iter = input.split_whitespace();
    let x_plate: i32 = iter.next().unwrap().parse().unwrap(); // protects from code injection
    let y_plate: i32 = iter.next().unwrap().parse().unwrap();
    let main_retangulo : Retangulo = Retangulo::new(x_plate, y_plate, 0);
    
    //read the number different ways to cut a plate
    std::io::stdin().read_line(&mut input).unwrap();
    let number_of_plates: i32 = input.trim().parse().unwrap();

    //read n values and add to the priority queue
    let mut retangulo_queue: VecDeque<Retangulo> = VecDeque::new();
    
    for _ in 0..number_of_plates {
        let mut input = String::new();
        std::io::stdin().read_line(&mut input).unwrap();
        let mut iter = input.split_whitespace();
        let x: i32 = iter.next().unwrap().parse().unwrap(); // protects from code injection
        let y: i32 = iter.next().unwrap().parse().unwrap();
        let price: i32 = iter.next().unwrap().parse().unwrap();
        retangulo_queue.push_back(Retangulo {x, y, price});
    }
    for _ in 0..number_of_plates{
        print!("{} ", retangulo_queue.pop_front().unwrap().how_many_can_fit(&main_retangulo));
    }
    
}
