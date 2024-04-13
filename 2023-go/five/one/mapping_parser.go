package one

import (
	"regexp"
	"strconv"
)

type MappingParser struct {
	numberPattern *regexp.Regexp
}

func NewMappingParser(in chan string) chan Mapping {
	mp := MappingParser{
		numberPattern: regexp.MustCompile(`^(\d+) (\d+) (\d+)$`),
	}

	return NewPipelineStep(in, mp.parseMapping)
}

func (mp *MappingParser) parseMapping(line string) Mapping {
	matches := mp.numberPattern.FindStringSubmatch(line)

	dest, _ := strconv.Atoi(matches[1])
	src, _ := strconv.Atoi(matches[2])
	rng, _ := strconv.Atoi(matches[3])

	return Mapping{
		start: src,
		end: src + rng - 1,
		mod: dest - src,
	}
}
