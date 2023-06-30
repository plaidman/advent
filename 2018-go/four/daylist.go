package four

type DayList struct {
	days map[string]*Day
}

func NewDayList() DayList {
	days := make(map[string]*Day)

	return DayList{days: days}
}

func (d DayList) checkAndAppend(date string) *Day {
	dayPtr, exists := d.days[date]

	if !exists {
		day := NewDay()
		dayPtr = &day
		d.days[date] = dayPtr
	}

	return dayPtr
}
