import { green, red } from 'chalk';

export class Logger {
    public error(message: string): void {
        console.log(red(message));
    }

    public log(message: string): void {
        console.log(message);
    }

    public answer(message: string | number): void {
        console.log(green(message));
    }
}
