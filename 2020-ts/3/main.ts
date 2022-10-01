import { Logger } from '../Logger';
import { InputReader } from '../InputReader';

const logger = new Logger();
const reader = new InputReader();

function main() {
    const map = reader.readInput('3/input.txt');

    let answer = findTrees(3, 1, map);

    logger.answer(answer);

    answer *= findTrees(1, 1, map);
    answer *= findTrees(5, 1, map);
    answer *= findTrees(7, 1, map);
    answer *= findTrees(1, 2, map);

    logger.answer(answer);
}

function findTrees(right: number, down: number, map: string[]): number {
    let numTrees = 0;

    const width = map[0].length;
    const height = map.length;
    const current = { x: 0, y: 0 };

    while (current.y < height - 1) {
        current.y += down;
        current.x += right;

        if (current.x >= width) {
            current.x = current.x % width;
        }

        if (map[current.y][current.x] === '#') {
            numTrees++;
        }
    }

    return numTrees;
}

main();
