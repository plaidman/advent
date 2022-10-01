import { InputReader } from '../InputReader';
import { Logger } from '../Logger';

const logger = new Logger();
const reader = new InputReader();

function main() {
    const lines = reader.readInput('14/input.txt');
    const memory: Record<number, number> = {};
    let mask: string = '0'.repeat(36);

    for (const line of lines) {
        if (line.substr(0, 3) === 'mas') {
            const regex = /^mask = ([01X]{36})$/;
            [, mask] = regex.exec(line) ?? ['', 'xx'];
            continue;
        }

        const regex = /^mem\[([0-9]+)\] = ([0-9]+)$/;
        const [, addr, value] = regex.exec(line) ?? ['', 'xx', 'xx'];

        const maskedAddr = applyMask(parseInt(addr), mask);
        writeMemory(memory, maskedAddr, parseInt(value));
    }

    let sum = 0;
    for (const value of Object.values(memory)) {
        sum += value;
    }
    logger.answer(sum);
}

function writeMemory(memory: Record<number, number>, maskedAddr: string, value: number) {
    const xIndex = maskedAddr.indexOf('X');

    if (xIndex === -1) {
        memory[parseInt(maskedAddr, 2)] = value;
        return;
    }

    writeMemory(memory, maskedAddr.replace('X', '1'), value);
    writeMemory(memory, maskedAddr.replace('X', '0'), value);
}

function applyMask(num: number, mask: string): string {
    const bits = num.toString(2).padStart(36, '0');
    let maskedBits = '';

    for (let i = 0; i < bits.length; i++) {
        if (mask[i] === '0') {
            maskedBits = `${maskedBits}${bits[i]}`;
            continue;
        }

        maskedBits = `${maskedBits}${mask[i]}`;
    }

    return maskedBits;
}

main();
