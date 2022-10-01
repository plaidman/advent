import { InputReader } from '../InputReader';
import { Logger } from '../Logger';

const reader = new InputReader();
const logger = new Logger();

function main() {
    const lines = reader.readInput('9/input.txt');

    const windowSize = 25;
    const window: number[] = [];
    for (let i = 0; i < windowSize; i++) {
        window[i] = parseInt(lines[i]);
    }

    let weaknessIndex = 0;
    for (let i = windowSize; i < lines.length; i++) {
        const currentNumber = parseInt(lines[i]);

        if (!validateNumber(window, currentNumber)) {
            weaknessIndex = i;
            break;
        }

        window.shift();
        window.push(currentNumber);
    }
    logger.answer(lines[weaknessIndex]);

    const numberSet = findNumberSet(lines, weaknessIndex);

    let min = Infinity;
    let max = -1;
    for (const number of numberSet) {
        if (number > max) max = number;
        if (number < min) min = number;
    }
    logger.answer(min + max);
}

function findNumberSet(lines: string[], weaknessIndex: number): number[] {
    const weaknessNumber = parseInt(lines[weaknessIndex]);

    let numberSet: number[] = [];
    for (let i = 0; i < weaknessIndex; i++) {
        numberSet = [];
        numberSet.push(parseInt(lines[i]));

        let sum = 0;
        for (let j = i + 1; j < weaknessIndex; j++) {
            numberSet.push(parseInt(lines[j]));

            sum = numberSet.reduce((acc, cur) => {
                return acc + cur;
            });

            if (sum >= weaknessNumber) break;
        }

        if (sum === weaknessNumber) break;
    }

    return numberSet;
}

function validateNumber(window: number[], target: number): boolean {
    const windowSize = window.length;

    for (let i = 0; i < windowSize; i++) {
        for (let j = i + 1; j < windowSize; j++) {
            if (window[i] + window[j] === target) return true;
        }
    }

    return false;
}

main();
