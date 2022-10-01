import { Logger } from '../Logger';
import { InputReader } from '../InputReader';

const logger = new Logger();
const reader = new InputReader();

function main() {
    const expenses = reader.readInput('1/input.txt');

    for (let i = 0; i < expenses.length; i++) {
        for (let j = i + 1; j < expenses.length; j++) {
            const eye = parseInt(expenses[i]);
            const jay = parseInt(expenses[j]);

            if (eye + jay === 2020) {
                logger.answer(eye * jay);
            }
        }
    }

    for (let i = 0; i < expenses.length; i++) {
        for (let j = i + 1; j < expenses.length; j++) {
            for (let k = j + 1; k < expenses.length; k++) {
                const eye = parseInt(expenses[i]);
                const jay = parseInt(expenses[j]);
                const kay = parseInt(expenses[k]);

                if (eye + jay + kay === 2020) {
                    logger.answer(eye * jay * kay);
                }
            }
        }
    }
}

main();
