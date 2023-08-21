use super::worker::Worker;

const IS_TEST: bool = true;

pub fn run(lines: Vec<String>) {
    let step_padding = if IS_TEST { 0 } else { 60 };
    let num_workers = if IS_TEST { 2 } else { 5 };

    let mut workers = Vec::<Worker>::new();
    for _ in 0..num_workers {
        workers.push(Worker::new());
    }

    for worker in workers.iter() {}
}
