import { InputReader } from '../InputReader';
import { Logger } from '../Logger';

const logger = new Logger();
const reader = new InputReader();

type Group = Record<string, number>;

function main() {
    const lines = reader.readInput('6/input.txt');
    const groups = normalizeGroups(lines);

    let total = 0;
    for (const group of groups) {
        total += Object.keys(group).length - 1;
    }
    logger.answer(total);

    total = 0;
    for (const group of groups) {
        for (const question of Object.keys(group)) {
            if (question === 'people') continue;
            if (group[question] === group.people) total++;
        }
    }
    logger.answer(total);
}

function normalizeGroups(lines: string[]): Group[] {
    const groups: Group[] = [];
    let group: Group = { people: 0 };
    let lineIndex = 0;

    while (lineIndex < lines.length) {
        if (lines[lineIndex] === '') {
            groups.push(group);

            group = { people: 0 };
            lineIndex++;
            continue;
        }

        for (const question of lines[lineIndex]) {
            if (group[question] === undefined) group[question] = 0;
            group[question]++;
        }
        group.people++;

        lineIndex++;
    }

    return groups;
}

main();
