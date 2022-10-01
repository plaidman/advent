import { InputReader } from '../InputReader';
import { Logger } from '../Logger';

const logger = new Logger();
const reader = new InputReader();

type Rule = { min1: number; max1: number; min2: number; max2: number };
type RuleSet = Record<string, Rule>;

function main() {
    const lines = reader.readInput('16/input.txt');
    const { myTicket, rules, otherTickets } = parseInput(lines);

    const { sumErrorRate, goodTickets } = findGoodTickets(otherTickets, rules);
    goodTickets.push(myTicket);
    logger.answer(sumErrorRate);

    const possibleColumns = findPossibleColumns(rules, goodTickets);
    const foundColumns = reducePossibleColumns(possibleColumns);

    let result = 1;
    for (const key of Object.keys(foundColumns)) {
        if (key.substr(0, 9) !== 'departure') continue;

        const column = foundColumns[key];
        result *= myTicket[column];
    }
    logger.answer(result);
}

function reducePossibleColumns(possibleColumns: Record<string, number[]>): Record<string, number> {
    const foundColumns: Record<string, number> = {};

    // eslint-disable-next-line no-constant-condition
    while (true) {
        for (const key of Object.keys(possibleColumns)) {
            if (foundColumns[key] !== undefined) continue;

            if (possibleColumns[key].length === 1) {
                foundColumns[key] = possibleColumns[key][0];
                removePossibilityFromAllColumns(possibleColumns, key);
            }
        }

        if (Object.keys(foundColumns).length === Object.keys(possibleColumns).length) {
            break;
        }
    }

    return foundColumns;
}

function removePossibilityFromAllColumns(possibleColumns: Record<string, number[]>, key: string) {
    for (const columnKey of Object.keys(possibleColumns)) {
        if (columnKey === key) continue;

        possibleColumns[columnKey] = possibleColumns[columnKey].filter((value) => value !== possibleColumns[key][0]);
    }
}

function findPossibleColumns(rules: RuleSet, goodTickets: number[][]): Record<string, number[]> {
    const columns: Record<string, number[]> = {};

    for (const key of Object.keys(rules)) {
        if (columns[key] === undefined) columns[key] = [];

        for (let i = 0; i < goodTickets[0].length; i++) {
            let valid = true;

            for (const ticket of goodTickets) {
                if (isNumberValidForRule(ticket[i], rules[key]) === false) {
                    valid = false;
                    break;
                }
            }

            if (valid === true) {
                columns[key].push(i);
            }
        }
    }

    return columns;
}

function findGoodTickets(tickets: number[][], rules: RuleSet) {
    const goodTickets: number[][] = [];
    let sumErrorRate = 0;

    for (const ticket of tickets) {
        let valid = true;

        for (const num of ticket) {
            if (isNumberValidForAnyRule(num, rules) === false) {
                sumErrorRate += num;
                valid = false;
            }
        }

        if (valid === true) {
            goodTickets.push(ticket);
        }
    }

    return { sumErrorRate, goodTickets };
}

function isNumberValidForAnyRule(num: number, rules: RuleSet): boolean {
    for (const key of Object.keys(rules)) {
        if (isNumberValidForRule(num, rules[key]) === true) return true;
    }

    return false;
}

function isNumberValidForRule(num: number, rule: Rule): boolean {
    if (rule.max1 >= num && rule.min1 <= num) return true;
    if (rule.max2 >= num && rule.min2 <= num) return true;
    return false;
}

function parseInput(lines: string[]) {
    const rules: RuleSet = {};
    const otherTickets: number[][] = [];

    let i = 0;
    for (i; i < lines.length; i++) {
        const line = lines[i];
        const regex = /^([a-z ]+): ([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+)$/;
        const matches = regex.exec(line);

        if (matches === null) {
            break;
        }

        const [, name, min1, max1, min2, max2] = matches;
        rules[name] = {
            min1: parseInt(min1),
            max1: parseInt(max1),
            min2: parseInt(min2),
            max2: parseInt(max2),
        };
    }

    i += 2;
    const myTicket = lines[i].split(',').map((num) => parseInt(num));

    i += 3;
    for (i; i < lines.length; i++) {
        const otherTicket = lines[i].split(',').map((num) => parseInt(num));
        otherTickets.push(otherTicket);
    }

    return { myTicket, rules, otherTickets };
}

main();
