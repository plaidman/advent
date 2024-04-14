package one

import (
	"regexp"
	"strconv"
)

type HandParser struct {
	handPattern regexp.Regexp
}

func NewHandParser(in chan string) chan Hand {
	hp := HandParser{
		handPattern: *regexp.MustCompile(`^(.)(.)(.)(.)(.) (\d+)$`),
	}
	return NewPipelineStep(in, hp.parseHand)
}

func (hp *HandParser) parseHand(in string) Hand {
	matches := hp.handPattern.FindStringSubmatch(in)

	cardOne := parseCardNum(matches[1])
	cardTwo := parseCardNum(matches[2])
	cardThree := parseCardNum(matches[3])
	cardFour := parseCardNum(matches[4])
	cardFive := parseCardNum(matches[5])

	bid, _ := strconv.Atoi(matches[6])

	return Hand{
		cards: [5]int{cardOne, cardTwo, cardThree, cardFour, cardFive},
		rank:  0,
		bid:   bid,
	}
}

func parseCardNum(in string) int {
	if in == "A" { return 14 }
	if in == "K" { return 13 }
	if in == "Q" { return 12 }
	if in == "J" { return 11 }
	if in == "T" { return 10 }

	cardNum, _ := strconv.Atoi(in)

	return cardNum
}
