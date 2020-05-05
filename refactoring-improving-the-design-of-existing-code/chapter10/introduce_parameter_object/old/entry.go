package old

import "time"

type Entry struct {
	value      float64
	chargeDate time.Time
}

func (e *Entry) GetDate() time.Time {
	return e.chargeDate
}

func (e *Entry) GetValue() float64 {
	return e.value
}

type Account struct {
	entries []*Entry
}

func (a *Account) GetFlowBetween(start, end time.Time) float64 {
	result := 0.0
	for i := range a.entries {
		entry := a.entries[i]
		date := entry.GetDate()
		if date == start || date == end || date.After(start) && date.Before(end) {
			result += entry.GetValue()
		}
	}
	return result
}
