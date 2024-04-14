package one

import (
	"bufio"
	"fmt"
	"regexp"
	"strconv"
)

func RunPart(scanner *bufio.Scanner) {
	scanner.Scan()
	timeLine := scanner.Text()
	scanner.Scan()
	distLine := scanner.Text()

	raceChan := make(chan Race)
	countChan := NewWinningOptsCounter(raceChan)
	accum := NewMultAccumulator(countChan)

	parseRaces(timeLine, distLine, raceChan)
	close(raceChan)

	fmt.Println("result:", <-accum)
}

func parseRaces(timeLine string, distLine string, out chan Race) {
	racesPattern := regexp.MustCompile(`(\d+)`)
	timeMatches := racesPattern.FindAllString(timeLine, -1)
	distMatches := racesPattern.FindAllString(distLine, -1)

	for i := 0; i < len(timeMatches); i++ {
		time, _ := strconv.Atoi(timeMatches[i])
		dist, _ := strconv.Atoi(distMatches[i])

		out <- Race{ time, dist }
	}
}
