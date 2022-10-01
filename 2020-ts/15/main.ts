import { Logger } from '../Logger';

const logger = new Logger();

function main() {
    const history: Record<number, number[]> = {};
    // const line = '0,3,6'; // 436;
    // const line = '1,3,2'; // 1;
    // const line = '2,1,3' // 10;
    // const line = '1,2,3' // 27;
    // const line = '2,3,1' // 78;
    // const line = '3,2,1' // 438;
    // const line = '3,1,2' // 1836;
    const line = '11,18,0,20,1,7,16'; // 639

    const nums = line.split(',').map((num) => {
        return parseInt(num);
    });

    let lastNum = 0;
    let i = 0;
    for (i; i < nums.length; i++) {
        lastNum = nums[i];
        addNumber(history, lastNum, i + 1);
    }

    for (i; i < 30000000; i++) {
        const numHistory = history[lastNum];

        if (i % 100000 === 0) console.log(`${((100.0 * i) / 30000000).toFixed(3)}%`);

        if (numHistory.length === 1) {
            lastNum = 0;
        } else {
            lastNum = numHistory[numHistory.length - 1] - numHistory[numHistory.length - 2];
        }

        addNumber(history, lastNum, i + 1);
    }

    logger.answer(lastNum);
}

function addNumber(history: Record<number, number[]>, num: number, index: number): void {
    if (history[num] === undefined) {
        history[num] = [index];
        return;
    }

    history[num].push(index);

    if (history[num].length > 3) {
        history[num].unshift();
    }
}

main();
