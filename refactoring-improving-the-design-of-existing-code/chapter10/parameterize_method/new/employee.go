package new

type Employee struct {
	salary float64
}

func (e *Employee) Raise(factor float64) {
	e.salary *= 1 + factor
}
