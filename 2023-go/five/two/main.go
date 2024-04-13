package two

import (
	"bufio"
	"fmt"
	"regexp"
	"strconv"
)

type SeedRange struct {
	start int
	end int
}

func RunPart(scanner *bufio.Scanner) {
	scanner.Scan() // seed line
	seedLine := scanner.Text()
	scanner.Scan() // blank line
	scanner.Scan() // label line

	allSteps := parseAlmanacGroups(scanner)
	seedRanges := parseSeedRanges(seedLine)

	inRange := false
	for i := 0; inRange == false; i++ {
		seed := findSeed(i, allSteps)
		inRange = inSeedRanges(seed, seedRanges)

		if i % 10000000 == 0 {
			fmt.Println(i)
		}

		if inRange {
			fmt.Println("lowest location:", i)
			break;
		}
	}
}

func inSeedRanges(seed int, seedRanges []SeedRange) bool {
	for _, seedRange := range seedRanges {
		if seed <= seedRange.end && seed >= seedRange.start {
			return true
		}
	}
	return false
}

func parseAlmanacGroups(scanner *bufio.Scanner) []ProductionStep {
	linesChan := make(chan []string)
	productionStepChan := NewProductionStepParser(linesChan)
	allStepsChan := NewSliceAccumulator(productionStepChan)

	almanacGroup := make([]string, 0)
	for scanner.Scan() {
		line := scanner.Text()

		if line == "" {
			linesChan <- almanacGroup
			almanacGroup = make([]string, 0)
			scanner.Scan() // skip label line
			continue
		}

		almanacGroup = append(almanacGroup, line)
	}
	linesChan <- almanacGroup
	close(linesChan)

	return <-allStepsChan
}

func parseSeedRanges(line string) []SeedRange {
	seedRanges := make([]SeedRange, 0)

	pattern := regexp.MustCompile(`(\d+) (\d+)`)
	matches := pattern.FindAllStringSubmatch(line, -1)

	for _, match := range matches {
		start, _ := strconv.Atoi(match[1])
		length, _ := strconv.Atoi(match[2])
		end := start + length - 1

		seedRanges = append(seedRanges, SeedRange{start, end})
	}

	return seedRanges
}

func findSeed(location int, allSteps []ProductionStep) int {
	humidity := allSteps[6].mapNumber(location)
	temp := allSteps[5].mapNumber(humidity)
	light := allSteps[4].mapNumber(temp)
	water := allSteps[3].mapNumber(light)
	fertilizer := allSteps[2].mapNumber(water)
	soil := allSteps[1].mapNumber(fertilizer)
	return allSteps[0].mapNumber(soil)
}

