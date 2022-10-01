import { InputReader } from '../InputReader';
import { Logger } from '../Logger';

const logger = new Logger();
const reader = new InputReader();

type Document = Record<string, string>;
type AttrValidationFunc = (arg0: string) => boolean;
type AttrValidationSet = Record<string, AttrValidationFunc>;

function main() {
    const lines = reader.readInput('4/input.txt');
    const documents = normalizeDocuments(lines);

    const validKeys = documents.filter((doc) => {
        return validateAttrKeys(doc);
    });
    logger.answer(validKeys.length);

    const validValues = validKeys.filter((doc) => {
        return validateAttrValues(doc);
    });
    logger.answer(validValues.length);
}

function validateAttrValues(doc: Document): boolean {
    for (const key of Object.keys(doc)) {
        const validator = valueValidators[key];
        if (validator(doc[key]) === false) {
            return false;
        }
    }

    return true;
}

const valueValidators: AttrValidationSet = {
    byr: (value: string) => {
        const num = parseInt(value);
        return num <= 2002 && num >= 1920;
    },

    iyr: (value: string) => {
        const num = parseInt(value);
        return num <= 2020 && num >= 2010;
    },

    eyr: (value: string) => {
        const num = parseInt(value);
        return num <= 2030 && num >= 2020;
    },

    hgt: (value: string) => {
        const regex = /^([0-9]+)(cm|in)$/;
        const [, amountString, units] = regex.exec(value) ?? ['', 'xx', 'xx'];

        const amount = parseInt(amountString);

        if (units === 'cm' && amount <= 193 && amount >= 150) return true;
        if (units === 'in' && amount <= 76 && amount >= 59) return true;
        return false;
    },

    hcl: (value: string) => {
        const regex = /^#[0-9a-f]{6}$/;
        return regex.test(value);
    },

    ecl: (value: string) => {
        const validECL = ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth'];
        return validECL.includes(value);
    },

    pid: (value: string) => {
        const regex = /^[0-9]{9}$/;
        return regex.test(value);
    },

    cid: () => {
        return true;
    },
};

function validateAttrKeys(doc: Document): boolean {
    const validKeys = ['byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid'];

    for (const key of validKeys) {
        if (doc[key] === undefined) {
            return false;
        }
    }

    return true;
}

function normalizeDocuments(lines: string[]): Document[] {
    const documents: Document[] = [];

    let currentLine = '';
    let lineIndex = 0;

    while (lineIndex < lines.length) {
        if (lines[lineIndex] === '') {
            documents.push(buildDocument(currentLine));

            currentLine = '';
            lineIndex++;
            continue;
        }

        if (currentLine.length > 0) {
            currentLine = currentLine.concat(' ');
        }
        currentLine = currentLine.concat(lines[lineIndex]);
        lineIndex++;
    }

    return documents;
}

function buildDocument(line: string): Document {
    const lineItems = line.split(' ');
    const document: Document = {};

    for (const lineItem of lineItems) {
        const [key, value] = lineItem.split(':');
        document[key] = value;
    }

    return document;
}

main();
