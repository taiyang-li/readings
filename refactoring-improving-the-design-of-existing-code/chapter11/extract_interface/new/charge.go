package new

func Charge(b Billable, days int) float64 {
	base := float64(b.GetRate() * days)
	if b.HasSpecialSkill() {
		return base * 1.05
	} else {
		return base
	}
}

type Billable interface {
	GetRate() int
	HasSpecialSkill() bool
}

type Employee struct {
	rate            int
	hasSpecialSkill bool
}

func NewEmployee(rate int, hasSpecialSkill bool) *Employee {
	return &Employee{
		rate:            rate,
		hasSpecialSkill: hasSpecialSkill,
	}
}

func (e *Employee) GetRate() int {
	return e.rate
}

func (e *Employee) HasSpecialSkill() bool {
	return e.hasSpecialSkill
}
