import { InputReader } from '../InputReader';
import { Logger } from '../Logger';

const logger = new Logger();
const reader = new InputReader();

type Position = { x: number; y: number; h: number; wx: number; wy: number };
type MoveFunction = (pos: Position, dist: number) => void;
type Direction = 'N' | 'S' | 'E' | 'W' | 'F' | 'R' | 'L';
type MoveMap = Record<Direction, MoveFunction>;

function main() {
    const lines = reader.readInput('12/input.txt');
    const position: Position = { x: 0, y: 0, h: 0, wx: 10, wy: 1 };
    const regex = /^([NSEWFRL])([0-9]+)$/;

    for (const line of lines) {
        const [, dir, dist] = regex.exec(line) ?? ['', 'xx', 'xx'];
        const moveFunction = shipMovements[dir as Direction];
        moveFunction(position, parseInt(dist));
    }
    logger.answer(Math.abs(position.x) + Math.abs(position.y));

    position.x = 0;
    position.y = 0;
    for (const line of lines) {
        const [, dir, dist] = regex.exec(line) ?? ['', 'xx', 'xx'];
        const moveFunction = waypointMovements[dir as Direction];
        moveFunction(position, parseInt(dist));
    }
    logger.answer(Math.abs(position.x) + Math.abs(position.y));
}

const waypointMovements: MoveMap = {
    N: (pos, dist) => {
        pos.wy += dist;
    },
    S: (pos, dist) => {
        pos.wy -= dist;
    },
    E: (pos, dist) => {
        pos.wx += dist;
    },
    W: (pos, dist) => {
        pos.wx -= dist;
    },
    F: (pos, dist) => {
        pos.x += pos.wx * dist;
        pos.y += pos.wy * dist;
    },
    R: (pos, dist) => {
        const x = pos.wx;
        const y = pos.wy;

        if (dist === 90) {
            pos.wx = y;
            pos.wy = -1 * x;
        }
        if (dist === 180) {
            pos.wx = -1 * x;
            pos.wy = -1 * y;
        }
        if (dist === 270) {
            pos.wx = -1 * y;
            pos.wy = x;
        }
    },
    L: (pos, dist) => {
        if (dist === 90) waypointMovements.R(pos, 270);
        if (dist === 180) waypointMovements.R(pos, 180);
        if (dist === 270) waypointMovements.R(pos, 90);
    },
};

const shipMovements: MoveMap = {
    N: (pos, dist) => {
        pos.y += dist;
    },
    S: (pos, dist) => {
        pos.y -= dist;
    },
    E: (pos, dist) => {
        pos.x += dist;
    },
    W: (pos, dist) => {
        pos.x -= dist;
    },
    F: (pos, dist) => {
        if (pos.h === 0) shipMovements.E(pos, dist);
        else if (pos.h === 90) shipMovements.S(pos, dist);
        else if (pos.h === 180) shipMovements.W(pos, dist);
        else if (pos.h === 270) shipMovements.N(pos, dist);
    },
    R: (pos, dist) => {
        pos.h += dist;
        pos.h = mod(pos.h, 360);
    },
    L: (pos, dist) => {
        pos.h -= dist;
        pos.h = mod(pos.h, 360);
    },
};

function mod(n: number, m: number): number {
    while (n >= m) n -= m;
    while (n < 0) n += m;
    return n;
}

main();
