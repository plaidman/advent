import { InputReader } from '../InputReader';
import { Logger } from '../Logger';

const reader = new InputReader();
const logger = new Logger();

type InnerBags = Record<string, number>;
type OuterBags = Record<string, InnerBags>;

function main() {
    const lines = reader.readInput('7/input.txt');
    const bags: OuterBags = {};

    for (const line of lines) {
        const result = processOuterBag(line);
        bags[result.outerBag] = processInnerBags(result.innerBags);
    }

    const shinyGoldOuterBags = findOuterBags(bags, 'shiny gold', {});
    logger.answer(Object.keys(shinyGoldOuterBags).length);

    const shinyGoldInnerBags = countInnerBags(bags, 'shiny gold');
    logger.answer(shinyGoldInnerBags);
}

function countInnerBags(bags: OuterBags, bagName: string): number {
    const bag = bags[bagName];
    let count = 0;

    for (const innerBagName of Object.keys(bag)) {
        const quantity = bag[innerBagName];
        count += quantity;
        count += countInnerBags(bags, innerBagName) * quantity;
    }

    return count;
}

function findOuterBags(
    bags: OuterBags,
    innerBagName: string,
    collection: Record<string, boolean>,
): Record<string, boolean> {
    for (const bagName of Object.keys(bags)) {
        if (collection[bagName] !== undefined) continue;

        if (bags[bagName][innerBagName] !== undefined) {
            collection[bagName] = true;
            collection = {
                ...collection,
                ...findOuterBags(bags, bagName, collection),
            };
        }
    }

    return collection;
}

function processInnerBags(innerBagString: string): InnerBags {
    const regex = /([0-9]+) ([a-z]+ [a-z]+)/g;
    const innerBags: InnerBags = {};

    // eslint-disable-next-line no-constant-condition
    while (true) {
        const [, amount, bagName] = regex.exec(innerBagString) ?? ['', 'xx', 'xx'];

        if (bagName === 'xx') {
            break;
        }

        innerBags[bagName] = parseInt(amount);
    }

    return innerBags;
}

function processOuterBag(line: string) {
    const regex = /^([a-z ]+) bags contain (.+)$/;
    const [, outerBag, innerBags] = regex.exec(line) ?? ['', 'xx', 'xx'];

    return { outerBag, innerBags };
}

main();
