import { InputReader } from '../InputReader';
import { Logger } from '../Logger';

const logger = new Logger();
const reader = new InputReader();

function main() {
    const tickets = reader.readInput('5/input.txt');
    const ticketNums: boolean[] = [];
    let max = 0;

    for (const ticket of tickets) {
        const ticketNum = generateId(ticket);
        ticketNums[ticketNum] = true;
        if (ticketNum > max) max = ticketNum;
    }

    logger.answer(max);

    for (let i = max; i >= 0; i--) {
        if (ticketNums[i] === undefined) {
            logger.answer(i);
            break;
        }
    }
}

function generateId(ticket: string): number {
    const ticketBinary = ticket.replace(/R|B/g, '1').replace(/L|F/g, '0');
    return parseInt(ticketBinary, 2);
}

main();
