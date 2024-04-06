package one

import (
	"bufio"
	"fmt"
	"sync"
	"time"
)

var digits = map[string]int{
	"1": 1, "one": 1,
	"2": 2, "two": 2,
	"3": 3, "three": 3,
	"4": 4, "four": 4,
	"5": 5, "five": 5,
	"6": 6, "six": 6,
	"7": 7, "seven": 7,
	"8": 8, "eight": 8,
	"9": 9, "nine": 9,
}

func RunPartTwo(scanner *bufio.Scanner) {
	var wg sync.WaitGroup
	line_out := make(chan int)
	sum_out := make(chan int)
	start := time.Now()

	go receive_line(line_out, sum_out)

	scanner.Split(bufio.ScanLines)
	for scanner.Scan() {
		line := scanner.Text()
		wg.Add(1)
		go parse_line(line, line_out, &wg)
	}

	wg.Wait()
	close(line_out)

	fmt.Println("calibration sum: ", <-sum_out)
	fmt.Println("duration: ", time.Since(start))
}

func receive_line(in chan int, out chan int) {
	sum := 0

	for i := range in {
		sum += i
	}

	out <- sum
}

func parse_line(line string, out chan int, wg *sync.WaitGroup) {
	defer wg.Done()

	tens_out := make(chan int)
	ones_out := make(chan int)

	go parse_tens(line, tens_out)
	go parse_ones(line, ones_out)

	sum := <-tens_out * 10
	sum += <-ones_out

	out <- sum
}

func parse_tens(line string, out chan int) {
	for i := 0; i < len(line); i++ {
		val, found := check_string(line[i:])

		if found {
			out <- val
			return
		}
	}

	panic(fmt.Sprint("didn't find a number: ", line))
}

func parse_ones(line string, out chan int) {
	for i := len(line)-1; i >= 0; i-- {
		val, found := check_string(line[i:])

		if found {
			out <- val
			return
		}
	}

	panic(fmt.Sprint("didn't find a number: ", line))
}

func check_string(in string) (int, bool) {
	for key, value := range digits {
		if len(in) < len(key) {
			continue
		}

		if in[:len(key)] == key {
			return value, true
		}
	}

	return 0, false
}
