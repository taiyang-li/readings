package old

import "time"

var (
	SUMMER_START time.Time
	SUMMER_END   time.Time
)

type A struct {
	date                time.Time
	quantity            int
	winterRate          float64
	winterServiceCharge float64
	summerRate          float64
}

func (a *A) Charge() float64 {
	var result float64
	if a.date.Before(SUMMER_START) || a.date.After(SUMMER_END) {
		result = float64(a.quantity)*a.winterRate + a.winterServiceCharge
	} else {
		result = float64(a.quantity) * a.summerRate
	}
	return result
}
