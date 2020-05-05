package old

type Employee struct {
	salary float64
}

func (e *Employee) TenPercentRaise() {
	e.salary *= 1.1
}

func (e *Employee) FivePercentRaise() {
	e.salary *= 1.05
}
