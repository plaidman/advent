import { InputReader } from '../InputReader';
import { Logger } from '../Logger';

const logger = new Logger();
const reader = new InputReader();

function main() {
    const lines = reader.readInput('14/input.txt');
    const memory: Record<number, number> = {};
    let mask: string = 'X'.repeat(36);

    for (const line of lines) {
        if (line.substr(0, 3) === 'mas') {
            const regex = /^mask = ([01X]{36})$/;
            [, mask] = regex.exec(line) ?? ['', 'xx'];
            continue;
        }

        const regex = /^mem\[([0-9]+)\] = ([0-9]+)$/;
        const [, addr, value] = regex.exec(line) ?? ['', 'xx', 'xx'];
        memory[parseInt(addr)] = applyMask(parseInt(value), mask);
    }

    let sum = 0;
    for (const value of Object.values(memory)) {
        sum += value;
    }
    logger.answer(sum);
}

function applyMask(num: number, mask: string): number {
    const bits = num.toString(2).padStart(36, '0');
    let maskedBits = '';

    for (let i = 0; i < bits.length; i++) {
        if (mask[i] === 'X') {
            maskedBits = `${maskedBits}${bits[i]}`;
            continue;
        }

        maskedBits = `${maskedBits}${mask[i]}`;
    }

    return parseInt(maskedBits, 2);
}

main();
