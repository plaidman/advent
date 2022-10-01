import { InputReader } from '../InputReader';
import { Logger } from '../Logger';

const logger = new Logger();
const reader = new InputReader();

function main() {
    const lines = reader.readInput('13/input.txt');
    const busIds = lines[1].split(',');

    let prev = 1;
    let skip = prev;
    let temp = 0;
    let next = 0;

    for (let i = 0; i < busIds.length; i++) {
        if (busIds[i] === 'x') continue;

        next = parseInt(busIds[i]);
        temp = incrementTime(prev, next, i, skip);
        skip = lcm(skip, next);
        prev = temp;
    }

    logger.answer(prev);
}

function lcm(x: number, y: number): number {
    if (x === 0 || y === 0) return 0;
    return (x * y) / gcd(x, y);
}

function gcd(x: number, y: number): number {
    while (y !== 0) {
        const temp = y;
        y = x % y;
        x = temp;
    }

    return x;
}

function incrementTime(prev: number, next: number, diff: number, skip: number): number {
    let mult = 0;

    while (prev + diff !== mult * next) {
        if (prev + diff < mult * next) {
            prev += skip;
            continue;
        }

        mult = Math.ceil((1.0 * (prev + diff)) / next);
    }

    return prev;
}

main();
