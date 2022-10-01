import { InputReader } from '../InputReader';
import { Logger } from '../Logger';

const logger = new Logger();
const reader = new InputReader();

type Pocket = Record<number, Layer>;
type Layer = Record<number, Row>;
type Row = Record<number, Cell>;
type Cell = boolean;
type Coords = { x: number; y: number; z: number };

function main() {
    const lines = reader.readInput('17/input.txt');
    let pocket: Pocket;
    let nextPocket: Pocket;
    let pocketSize: Coords;
    let nextPocketSize: Coords;
    const directions = initializeDirections();

    ({ pocket, pocketSize } = initializePocket(lines));

    for (let i = 0; i < 6; i++) {
        ({ nextPocket, nextPocketSize } = expandPocket(pocket, pocketSize));
        incrementPocket(pocket, nextPocket, nextPocketSize, directions);
        pocket = nextPocket;
        pocketSize = nextPocketSize;
    }

    let countActive = 0;
    for (let x = 0; x < pocketSize.x; x++) {
        for (let y = 0; y < pocketSize.y; y++) {
            for (let z = 0; z < pocketSize.z; z++) {
                if (pocket[x][y][z]) countActive++;
            }
        }
    }
    logger.answer(countActive);
}

function incrementPocket(pocket: Pocket, nextPocket: Pocket, nextPocketSize: Coords, directions: Coords[]) {
    for (let x = 0; x < nextPocketSize.x; x++) {
        for (let y = 0; y < nextPocketSize.y; y++) {
            for (let z = 0; z < nextPocketSize.z; z++) {
                let countActive = 0;

                for (let i = 0; i < directions.length; i++) {
                    const adjCoord = {
                        x: x + directions[i].x,
                        y: y + directions[i].y,
                        z: z + directions[i].z,
                    };

                    if (isActive(pocket, adjCoord)) countActive++;
                }

                if (isActive(pocket, { x, y, z }) && countActive < 2) nextPocket[x][y][z] = false;
                if (isActive(pocket, { x, y, z }) && countActive > 3) nextPocket[x][y][z] = false;
                if (!isActive(pocket, { x, y, z }) && countActive === 3) nextPocket[x][y][z] = true;
            }
        }
    }
}

function isActive(pocket: Pocket, coords: Coords): boolean {
    return pocket?.[coords.x]?.[coords.y]?.[coords.z] ?? false;
}

function expandPocket(pocket: Pocket, pocketSize: Coords) {
    const nextPocket: Pocket = {};
    const nextPocketSize: Coords = {
        x: pocketSize.x + 2,
        y: pocketSize.y + 2,
        z: pocketSize.z + 2,
    };

    for (let x = 0; x < nextPocketSize.x; x++) {
        if (nextPocket[x] === undefined) nextPocket[x] = {};
        const layer = nextPocket[x];

        for (let y = 0; y < nextPocketSize.y; y++) {
            if (layer[y] === undefined) layer[y] = {};
            const row = layer[y];

            for (let z = 0; z < nextPocketSize.z; z++) {
                if (row[z] === undefined) row[z] = false;

                if (!isBorder({ x, y, z }, nextPocketSize)) {
                    row[z] = pocket[x - 1][y - 1][z - 1];
                }
            }
        }
    }

    for (let x = pocketSize.x - 1; x >= 0; x--) {
        pocket[x + 1] = pocket[x];
        delete pocket[x];

        for (let y = pocketSize.y - 1; y >= 0; y--) {
            pocket[x + 1][y + 1] = pocket[x + 1][y];
            delete pocket[x + 1][y];

            for (let z = pocketSize.z - 1; z >= 0; z--) {
                pocket[x + 1][y + 1][z + 1] = pocket[x + 1][y + 1][z];
                delete pocket[x + 1][y + 1][z];
            }
        }
    }

    return { nextPocket, nextPocketSize };
}

function isBorder(coords: Coords, pocketSize: Coords): boolean {
    if (coords.x === 0) return true;
    if (coords.y === 0) return true;
    if (coords.z === 0) return true;
    if (coords.x === pocketSize.x - 1) return true;
    if (coords.y === pocketSize.y - 1) return true;
    if (coords.z === pocketSize.z - 1) return true;
    return false;
}

function initializePocket(lines: string[]) {
    const pocket: Pocket = {};
    const layer: Layer = {};

    const pocketSize: Coords = { x: 1, y: 0, z: 0 };

    for (let y = 0; y < lines.length; y++) {
        const row: Row = {};
        const line = lines[y];

        for (let z = 0; z < line.length; z++) {
            const char = line[z];
            row[z] = char === '#';
        }

        pocketSize.z = line.length;
        layer[y] = row;
    }

    pocketSize.y = lines.length;
    pocket[0] = layer;

    return { pocket, pocketSize };
}

function initializeDirections(): Coords[] {
    const directions: Coords[] = [];

    for (let x = -1; x < 2; x++) {
        for (let y = -1; y < 2; y++) {
            for (let z = -1; z < 2; z++) {
                if (x === 0 && y === 0 && z === 0) continue;
                directions.push({ x, y, z });
            }
        }
    }

    return directions;
}

main();
