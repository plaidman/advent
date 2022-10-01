import { InputReader } from '../InputReader';
import { Logger } from '../Logger';

const logger = new Logger();
const reader = new InputReader();

function main() {
    const lines = reader.readInput('10/input.txt');
    const joltages: number[] = [0];

    for (const line of lines) {
        joltages.push(parseInt(line));
    }
    joltages.sort((a, b) => {
        return a - b;
    });
    joltages.push(joltages[joltages.length - 1] + 3);

    const joltageDiffs: Record<number, number> = {};
    for (let i = 1; i < joltages.length; i++) {
        const diff = joltages[i] - joltages[i - 1];
        if (joltageDiffs[diff] === undefined) joltageDiffs[diff] = 0;
        joltageDiffs[diff]++;
    }
    logger.answer(joltageDiffs[1] * joltageDiffs[3]);

    const combinations = findCombinations(joltages);
    logger.answer(combinations);
}

function findCombinations(joltages: number[]): number {
    const paths = [1];

    for (let i = 1; i < joltages.length; i++) {
        paths[i] = 0;

        for (let j = 1; j < 4; j++) {
            if (i - j < 0) break;
            if (joltages[i] - 3 > joltages[i - j]) break;
            paths[i] += paths[i - j];
        }
    }

    return paths[paths.length - 1];
}

main();
