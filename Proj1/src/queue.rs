use std::collections::BinaryHeap;
use std::cmp::Ordering;

// Define your custom type
#[derive(Debug, Eq, PartialEq)]
struct KeyValueObject {
    key: String, // Replace with the actual type of your key
    value: i32,
}

impl Ord for KeyValueObject {
    fn cmp(&self, other: &Self) -> Ordering {
        // Reverse ordering to make it a max-heap based on the value
        self.value.cmp(&other.value)
    }
}

impl PartialOrd for KeyValueObject {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

fn main() {
    // Create a max heap (priority queue)
    let mut priority_queue = BinaryHeap::new();

    // Enqueue elements with their priorities
    priority_queue.push(KeyValueObject { key: "A".to_string(), value: 5 });
    priority_queue.push(KeyValueObject { key: "B".to_string(), value: 2 });
    priority_queue.push(KeyValueObject { key: "C".to_string(), value: 10 });
    priority_queue.push(KeyValueObject { key: "D".to_string(), value: 7 });

    // Dequeue elements (in descending order of priority)
    while let Some(item) = priority_queue.pop() {
        println!("Dequeued: {:?}", item);
    }
}