import { InputReader } from '../InputReader';
import { Logger } from '../Logger';

const logger = new Logger();
const reader = new InputReader();

type Rule = string[][];
type RuleSet = Record<number, Rule>;

function main() {
    const lines = reader.readInput('19/input.txt');
    const { rules, messages } = parseInput(lines);

    let regexString = compileValidator(rules, 0);
    regexString = `^${regexString.substr(1, regexString.length - 2)}$`;
    const regex = new RegExp(regexString);

    let count = 0;
    for (const message of messages) {
        if (regex.test(message)) {
            console.log(message.length);
            count++;
        }
    }
    logger.answer(count);
}

function compileValidator(rules: RuleSet, ruleNum: number): string {
    const orders = rules[ruleNum];

    const firstRule = orders[0][0];
    if (firstRule === '"a"' || firstRule === '"b"') return firstRule.substring(1, 2);

    let validator = '';
    for (const order of orders) {
        for (const rule of order) {
            validator = `${validator}${compileValidator(rules, parseInt(rule))}`;
        }
        validator = `${validator}|`;
    }

    return `(${validator.substr(0, validator.length - 1)})`;
}

function parseInput(lines: string[]) {
    const rules: RuleSet = {};
    const messages: string[] = [];

    let i = 0;
    for (i; i < lines.length; i++) {
        if (lines[i] === '') break;

        const lineRegex = /^([0-9]+): ([0-9 |"ab]+)$/;
        const [, ruleNumString, rule] = lineRegex.exec(lines[i]) ?? [];

        const orders: string[][] = [];
        const branches = rule.split(' | ');
        for (const branch of branches) {
            const order = branch.split(' ');
            orders.push(order);
        }

        const ruleNum = parseInt(ruleNumString);
        rules[ruleNum] = orders;
    }

    i++;
    for (i; i < lines.length; i++) {
        messages.push(lines[i]);
    }

    return { rules, messages };
}

main();
