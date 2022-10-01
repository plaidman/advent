type InstructionLogic = (value: number) => void;
type InstructionLogicSet = Record<string, InstructionLogic>;
type Step = { line: string; command: string; value: number; visited: number };
type Program = Step[];

export class Computer {
    public accumulator = 0;
    public programCounter = 0;
    public memory: Program = [];

    private instructionLogic: InstructionLogicSet = {
        acc: (value: number) => {
            this.accumulator += value;
            this.programCounter++;
        },

        jmp: (value: number) => {
            this.programCounter += value;
        },

        nop: () => {
            this.programCounter++;
        },
    };

    public initMemory(lines: string[]): void {
        this.programCounter = 0;
        this.accumulator = 0;
        this.memory = [];

        for (const line of lines) {
            this.memory.push(this.cacheCommand(line));
        }
    }

    public startProgram(): number {
        // eslint-disable-next-line no-constant-condition
        while (true) {
            if (this.programCounter >= this.memory.length) return 0;

            const line = this.memory[this.programCounter];

            if (line.visited === 1) {
                return 1;
            }

            const logic = this.instructionLogic[line.command];
            logic(line.value);
            line.visited = 1;
        }
    }

    private cacheCommand(line: string): Step {
        const regex = /^([a-z]{3}) ([+-][0-9]+)$/;
        const [, command, valueString] = regex.exec(line) ?? ['', 'xxx', '+0'];

        if (!Object.keys(this.instructionLogic).includes(command)) {
            throw new Error(`invalid instruction: ${line}`);
        }

        const value = parseInt(valueString);
        return { line, command, value, visited: 0 };
    }
}
