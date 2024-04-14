package two

import (
	"bufio"
	"fmt"
	"regexp"
	"strconv"
	"strings"
)

func RunPart(scanner *bufio.Scanner) {
	scanner.Scan()
	timeLine := strings.Replace(scanner.Text(), " ", "", -1)
	scanner.Scan()
	distLine := strings.Replace(scanner.Text(), " ", "", -1)

	race := parseRace(timeLine, distLine)

	fmt.Println("result:", race.CountWinningOpts())
}

func parseRace(timeLine string, distLine string) Race {
	racesPattern := regexp.MustCompile(`(\d+)`)
	timeMatches := racesPattern.FindAllString(timeLine, -1)
	distMatches := racesPattern.FindAllString(distLine, -1)

	time, _ := strconv.Atoi(timeMatches[0])
	dist, _ := strconv.Atoi(distMatches[0])

	return Race{ time, dist }
}
