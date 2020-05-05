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

func (a *Account) GetFlowBetween(dateRange *DateRange) float64 {
	result := 0.0
	for i := range a.entries {
		entry := a.entries[i]
		if dateRange.Includes(entry.GetDate()) {
			result += entry.GetValue()
		}
	}
	return result
}

type DateRange struct {
	start time.Time
	end   time.Time
}

func NewDateRange(start, end time.Time) *DateRange {
	return &DateRange{
		start: start,
		end:   end,
	}
}

func (r *DateRange) GetStart() time.Time {
	return r.start
}

func (r *DateRange) GetEnd() time.Time {
	return r.end
}

func (r *DateRange) Includes(date time.Time) bool {
	start := r.GetStart()
	end := r.GetEnd()
	return date == r.start || date == end || date.After(start) && date.Before(end)
}
