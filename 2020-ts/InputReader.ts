import { readFileSync } from 'fs';

export class InputReader {
    public readInput(filename: string): string[] {
        const inputBuffer = readFileSync(filename);
        const input = inputBuffer.toString();
        const inputArray = input.split('\n');

        return inputArray;
    }
}
