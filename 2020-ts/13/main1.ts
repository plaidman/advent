import { InputReader } from '../InputReader';
import { Logger } from '../Logger';

const logger = new Logger();
const reader = new InputReader();

function main() {
    const lines = reader.readInput('13/input.txt');
    const arrival = parseInt(lines[0]);
    const busIds: number[] = lines[1]
        .split(',')
        .filter((busId) => {
            return busId !== 'x';
        })
        .map((busId) => {
            return parseInt(busId);
        });

    let minRemainder = Infinity;
    let minBusId = 0;
    for (const busId of busIds) {
        const busArrival = incrementTime(arrival, busId);
        const remainder = busArrival % arrival;

        if (remainder < minRemainder) {
            minRemainder = remainder;
            minBusId = busId;
        }
    }
    logger.answer(minRemainder * minBusId);
}

function incrementTime(arrival: number, busId: number): number {
    let multiplier = 0;
    while (arrival > busId * multiplier) {
        multiplier++;
    }

    return busId * multiplier;
}

main();
