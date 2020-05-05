package old

const (
	ENGINEER = 0
	SALESMAN = 1
	MANAGER  = 2
)

type Employee struct {
	typ int
}

func NewEmployee(typ int) *Employee {
	return &Employee{
		typ: typ,
	}
}

func (e *Employee) GetType() int {
	return e.typ
}
