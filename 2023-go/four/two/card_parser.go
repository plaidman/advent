package two

import (
	"regexp"
	"strconv"
)

type CardParser struct {
	cardPattern *regexp.Regexp
	numberPattern *regexp.Regexp
}

func NewCardParser(in chan string) chan Card {
	parser := CardParser{
		cardPattern: regexp.MustCompile(`^Card +(\d)+: +([^\|]*) \| (.*)$`),
		numberPattern: regexp.MustCompile(`(\d+)`),
	}

	return NewPipelineStep(in, parser.parseLine)
}

func (p *CardParser) parseLine(line string) Card {
	matches := p.cardPattern.FindStringSubmatch(line)

	cardId, _ := strconv.Atoi(matches[1])

	winnerString := matches[2]
	winnerOut := make(chan []int)
	go p.parseNumberString(winnerString, winnerOut)

	haveString := matches[3]
	haveOut := make(chan []int)
	go p.parseNumberString(haveString, haveOut)

	return NewCard(cardId, <-winnerOut, <-haveOut)
}

func (p *CardParser) parseNumberString(
	numberString string,
	out chan []int,
) {
	numStrings := p.numberPattern.FindAllString(numberString, -1)
	numbers := make([]int, 0)

	for _, numString := range numStrings {
		number, _ := strconv.Atoi(numString)
		numbers = append(numbers, number)
	}

	out <- numbers
}
