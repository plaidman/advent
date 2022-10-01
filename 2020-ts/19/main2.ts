import { InputReader } from '../InputReader';
import { Logger } from '../Logger';

const logger = new Logger();
const reader = new InputReader();

type Rule = string[][];
type RuleSet = Record<number, Rule>;
type RegExpSet = Record<number, RegExp>;

// observations:
//   part 1 matches strings that are exactly 24 chars long
//   update to rule 8 adds increments of one extra length
//   update to rule 11 adds increments of two extra length
//   if length is less than 24, outright reject it
//   if length is exactly 24, use the regex from part 1
//   if length is 25, use the regex from part 1 but use the alternate rule for 8 once
//   generated a huge regex with all possibilities for a length, but I'm running out of memory
//   tried that, and I'm running out of memory somewhere. shrug. guess I don't get this star

function main() {
    const lines = reader.readInput('19/input.txt');
    const { rules, messages } = parseInput(lines);

    let maxLen = 0;
    for (const message of messages) {
        if (message.length > maxLen) maxLen = message.length;
    }

    const regexSet: RegExpSet = {};
    for (let i = 24; i <= maxLen; i++) {
        let target = i - 24;

        let single = 0;
        if (target % 2 === 1) {
            single = 1;
            target -= 1;
        }

        let double = target / 2;

        let regexStrings = '';
        while (double > 0) {
            const regexString = compileValidator(rules, 0, single, double);
            regexStrings = `${regexStrings}${regexString}|`;

            double--;
            single += 2;
        }

        regexSet[i] = new RegExp(regexStrings.substr(0, regexStrings.length - 1));
    }

    let count = 0;
    for (const message of messages) {
        console.log(count);

        const len = message.length;

        if (regexSet[len].test(message)) {
            count++;
        }
    }
    logger.answer(count);
}

function compileValidator(rules: RuleSet, ruleNum: number, single: number, double: number): string {
    let orders = rules[ruleNum];

    const firstRule = orders[0][0];
    if (firstRule === '"a"' || firstRule === '"b"') return firstRule.substring(1, 2);

    if (ruleNum === 8 && single > 0) {
        orders = [['42', '8']];
        single--;
    }

    if (ruleNum === 11 && double > 0) {
        orders = [['42', '11', '31']];
        double--;
    }

    let validator = '';
    for (const order of orders) {
        for (const rule of order) {
            validator = `${validator}${compileValidator(rules, parseInt(rule), single, double)}`;
        }
        validator = `${validator}|`;
    }

    return `(?:${validator.substr(0, validator.length - 1)})`;
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
