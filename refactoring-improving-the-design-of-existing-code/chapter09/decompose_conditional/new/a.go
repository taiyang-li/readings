package new

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
	if a.notSummer() {
		return a.winterCharge()
	} else {
		return a.summerCharge()
	}
}

func (a *A) notSummer() bool {
	return a.date.Before(SUMMER_START) || a.date.After(SUMMER_END)
}

func (a *A) summerCharge() float64 {
	return float64(a.quantity) * a.summerRate
}

func (a *A) winterCharge() float64 {
	return float64(a.quantity)*a.winterRate + a.winterServiceCharge
}
