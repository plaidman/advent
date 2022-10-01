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
        return calculateAddition(equation);
    }

    const [, innerEquation] = matches;
    const value = calculateAddition(innerEquation.substring(1, innerEquation.length - 1));
    return calculateParens(equation.replace(innerEquation, value));
}

function calculateAddition(equation: string): string {
    const nonParenRegex = /([0-9]+) \+ ([0-9]+)/;
    const matches = nonParenRegex.exec(equation);

    if (matches === null) {
        return calculateMultiplication(equation);
    }

    const [match, a, b] = matches;

    const value = parseInt(a) + parseInt(b);
    return calculateAddition(equation.replace(match, value.toString()));
}

function calculateMultiplication(equation: string): string {
    const nonParenRegex = /([0-9]+) \* ([0-9]+)/;
    const matches = nonParenRegex.exec(equation);

    if (matches === null) return equation;

    const [match, a, b] = matches;

    const value = parseInt(a) * parseInt(b);
    return calculateMultiplication(equation.replace(match, value.toString()));
}

main();
