package four

type DayList struct {
	days map[string]Day
}

func NewDayList() DayList {
	days := make(map[string]Day)

	return DayList{days: days}
}

func (d DayList) checkAndAppend(date string) Day {
	day, exists := d.days[date]

	if !exists {
		day = NewDay()
		d.days[date] = day
	}

	return day
}
