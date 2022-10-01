import { Logger } from '../Logger';
import { InputReader } from '../InputReader';

const logger = new Logger();
const reader = new InputReader();

function main() {
    const passwords = reader.readInput('2/input.txt');
    const validCount = [0, 0];

    for (const line of passwords) {
        const regex = /^([0-9]+)-([0-9]+) ([a-z]): ([a-z]+)$/;
        const [, min, max, letter, pass] = regex.exec(line) ?? [];

        if (validateOne(parseInt(min), parseInt(max), letter, pass)) {
            validCount[0]++;
        }

        if (validateTwo(parseInt(min), parseInt(max), letter, pass)) {
            validCount[1]++;
        }
    }

    logger.answer(validCount[0]);
    logger.answer(validCount[1]);
}

// eslint-disable-next-line @typescript-eslint/no-unused-vars
function validateOne(min: number, max: number, letter: string, pass: string) {
    let letterCount = 0;

    for (const passLetter of pass) {
        if (passLetter === letter) {
            letterCount++;
        }
    }

    return letterCount <= max && letterCount >= min;
}

// eslint-disable-next-line @typescript-eslint/no-unused-vars
function validateTwo(min: number, max: number, letter: string, pass: string) {
    if (pass[min - 1] === letter && pass[max - 1] !== letter) {
        return true;
    }

    if (pass[min - 1] !== letter && pass[max - 1] === letter) {
        return true;
    }

    return false;
}

main();
