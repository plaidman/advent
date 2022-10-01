import { InputReader } from '../InputReader';
import { Logger } from '../Logger';
import { Computer } from './Computer';

const logger = new Logger();
const reader = new InputReader();
const computer = new Computer();

function main() {
    const lines = reader.readInput('8/input.txt');

    computer.initMemory(lines);
    computer.startProgram();
    logger.answer(computer.accumulator);

    for (let i = 0; i < lines.length; i++) {
        const command = lines[i].substr(0, 3);

        if (command === 'acc') continue;

        computer.initMemory(lines);

        if (command === 'nop') {
            computer.memory[i].command = 'jmp';
        }

        if (command === 'jmp') {
            computer.memory[i].command = 'nop';
        }

        const result = computer.startProgram();
        if (result === 0) {
            logger.answer(computer.accumulator);
        }
    }
}

main();
