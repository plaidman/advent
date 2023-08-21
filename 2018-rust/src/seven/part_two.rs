use super::manual::Manual;
use super::worker::Worker;

const IS_TEST: bool = false;

/*
 * for some reason this code produces the right answer for the test input but it's off by one for the real input.
 * my code finishes a worker then tries to start a new task immediately.
 * I wonder if the intent is to have all workers finish then all workers try to pick up a task in turn.
 */

pub fn run(lines: Vec<String>) {
    let step_padding = if IS_TEST { 0 } else { 60 };
    let num_workers = if IS_TEST { 2 } else { 5 };

    let mut manual = Manual::new();
    for line in lines {
        manual.parse_line(line);
    }

    let mut workers = Vec::<Worker>::new();
    for _ in 0..num_workers {
        workers.push(Worker::new());
    }

    let mut timer = 0;
    loop {
        println!("");
        println!("current time: {}", timer);

        for worker in workers.iter_mut() {
            if worker.working {
                let is_done = worker.increment();

                if !is_done {
                    println!("  worker continuing task {}", worker.current);
                    continue;
                }

                let step = manual.get_step_mut_or_insert(worker.current);
                let children = step.finish_and_get_children();

                for child in children {
                    let child_step = manual.get_step_mut_or_insert(child);
                    child_step.remove_parent(worker.current);
                }

                println!("  worker finished task {}", worker.current);
            }

            worker.pick_up_new_task(&mut manual, step_padding);
        }

        if manual.all_done() {
            break;
        }

        timer += 1;
    }

    println!("all done! total time: {}", timer);
}
