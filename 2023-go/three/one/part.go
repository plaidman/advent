package one

type Part struct {
	row int
	start int
	end int
}

func NewPart(row int, start int, end int) *Part {
	return &Part{row, start, end}
}
