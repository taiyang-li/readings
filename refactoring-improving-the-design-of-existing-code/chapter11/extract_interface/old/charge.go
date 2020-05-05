package old

func Charge(emp *Employee, days int) float64 {
	base := float64(emp.GetRate() * days)
	if emp.HasSpecialSkill() {
		return base * 1.05
	} else {
		return base
	}
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
