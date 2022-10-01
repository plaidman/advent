import { InputReader } from '../InputReader';
import { Logger } from '../Logger';

const logger = new Logger();
const reader = new InputReader();

function main() {
    const equations = reader.readInput('18/input.txt');

    let sum = 0;
    for (const equation of equations) {
        const result = calculateParens(equation);
        console.log(result);
        sum += parseInt(result);
    }
    logger.answer(sum);
}

function calculateParens(equation: string): string {
    const parenRegex = /(\([^()]+\))/;
    const matches = parenRegex.exec(equation);

    if (matches === null) {
        return calculateNonParens(equation);
    }

    const [, innerEquation] = matches;
    const value = calculateNonParens(innerEquation.substring(1, innerEquation.length - 1));
    return calculateParens(equation.replace(innerEquation, value));
}

function calculateNonParens(equation: string): string {
    const nonParenRegex = /([0-9]+) ([+*]) ([0-9]+)/;
    const matches = nonParenRegex.exec(equation);

    if (matches === null) return equation;

    const [match, a, op, b] = matches;

    let value = 0;
    switch (op) {
        case '+': {
            value = parseInt(a) + parseInt(b);
            break;
        }

        case '*': {
            value = parseInt(a) * parseInt(b);
            break;
        }
    }

    return calculateNonParens(equation.replace(match, value.toString()));
}

main();
