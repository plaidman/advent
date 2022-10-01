import { InputReader } from '../InputReader';
import { Logger } from '../Logger';

const logger = new Logger();
const reader = new InputReader();

type TileChar = '.' | 'L';
enum TileType {
    occupied,
    empty,
    floor,
    wall,
}
type Tile = { types: TileType[] };
type UpdateTileFunc = (map: Tile[][], i: number, j: number, iter: number) => boolean;

function main() {
    // this can be optimized for memory space
    //   right now we're tracking the full history of every tile,
    //   and checking the Nth entry before adding the N+1th entry,
    //   then incrementing N after all tiles have been updated.
    //   if we rebuild a new map and overwrite the old one,
    //   the memory footprint may be reduced.
    //   I'm not sure how much this will affect computation time though.
    //   see puzzle 17

    const lines = reader.readInput('11/input.txt');
    let map = initMap(lines);

    let iter = runCycle(map, updateTileAdjacent);
    logger.answer(countOccupied(map, iter));

    map = initMap(lines);
    iter = runCycle(map, updateTileLOS);
    logger.answer(countOccupied(map, iter));
}

function runCycle(map: Tile[][], updateTileFunc: UpdateTileFunc): number {
    let equilibrium = false;
    let iter = 0;
    while (equilibrium === false) {
        equilibrium = true;

        for (let i = 0; i < map.length; i++) {
            const row = map[i];

            for (let j = 0; j < row.length; j++) {
                const updated = updateTileFunc(map, i, j, iter);
                if (updated === true) equilibrium = false;
            }
        }

        iter++;
    }

    return iter;
}

function initMap(lines: string[]): Tile[][] {
    const charmap: Record<TileChar, TileType> = {
        '.': TileType.floor,
        'L': TileType.empty,
    };
    const map: Tile[][] = [];

    for (const line of lines) {
        const row: Tile[] = [];

        for (const tile of line) {
            const type = charmap[tile as TileChar];
            row.push({ types: [type] });
        }

        map.push(row);
    }

    return map;
}

function countOccupied(map: Tile[][], iter: number): number {
    let sum = 0;

    for (const row of map) {
        for (const tile of row) {
            if (tile.types[iter] === TileType.occupied) sum++;
        }
    }

    return sum;
}

function updateTileLOS(map: Tile[][], i: number, j: number, iter: number): boolean {
    const tile = map[i][j];
    const curType = tile.types[iter];
    const directions = [
        { i: 1, j: 0 },
        { i: -1, j: 0 },
        { i: 0, j: 1 },
        { i: 0, j: -1 },
        { i: 1, j: 1 },
        { i: 1, j: -1 },
        { i: -1, j: 1 },
        { i: -1, j: -1 },
    ];

    if (curType === TileType.floor) {
        tile.types.push(TileType.floor);
        return false;
    }

    let countOccupied = 0;
    for (const dir of directions) {
        let adjTileType = TileType.floor;
        let dist = 0;
        while (adjTileType === TileType.floor) {
            dist++;
            adjTileType = getType(map, i + dir.i * dist, j + dir.j * dist, iter);
        }

        if (adjTileType === TileType.occupied) countOccupied++;
    }

    if (curType === TileType.empty && countOccupied === 0) {
        tile.types.push(TileType.occupied);
        return true;
    }

    if (curType === TileType.occupied && countOccupied >= 5) {
        tile.types.push(TileType.empty);
        return true;
    }

    tile.types.push(curType);
    return false;
}

function updateTileAdjacent(map: Tile[][], i: number, j: number, iter: number): boolean {
    const tile = map[i][j];
    const curType = tile.types[iter];
    const directions = [
        { i: 1, j: 0 },
        { i: -1, j: 0 },
        { i: 0, j: 1 },
        { i: 0, j: -1 },
        { i: 1, j: 1 },
        { i: 1, j: -1 },
        { i: -1, j: 1 },
        { i: -1, j: -1 },
    ];

    if (curType === TileType.floor) {
        tile.types.push(TileType.floor);
        return false;
    }

    let countOccupied = 0;
    for (const dir of directions) {
        if (getType(map, i + dir.i, j + dir.j, iter) === TileType.occupied) countOccupied++;
    }

    if (curType === TileType.empty && countOccupied === 0) {
        tile.types.push(TileType.occupied);
        return true;
    }

    if (curType === TileType.occupied && countOccupied >= 4) {
        tile.types.push(TileType.empty);
        return true;
    }

    tile.types.push(curType);
    return false;
}

function getType(map: Tile[][], i: number, j: number, iter: number): TileType {
    if (i < 0) return TileType.wall;
    if (i >= map.length) return TileType.wall;
    if (j < 0) return TileType.wall;
    if (j >= map[i].length) return TileType.wall;

    return map[i][j].types[iter];
}

main();
