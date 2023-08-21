use super::manual::Manual;
use super::worker::Worker;

const IS_TEST: bool = false;

/*
 * note: the description on this task is a little bit ambiguous.
 *
 * the previous commit code would loop through the workers, and pick up a new task immediately
 *   after the previous task was finished, then check the next worker
 * this would produce an answer that was one greater than the correct answer
 *
 * this code below produces the correct answer by finishing all workers in a loop,
 *   then pick up new tasks in a different loop
 *
 * the difference is subtle - test input is correct either way,
 *   but real input is incorrect with the previous commit's code.
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
        }

        for worker in workers.iter_mut() {
            worker.pick_up_new_task(&mut manual, step_padding)
        }

        if manual.all_done() {
            break;
        }

        timer += 1;
    }

    println!("all done! total time: {}", timer);
}
