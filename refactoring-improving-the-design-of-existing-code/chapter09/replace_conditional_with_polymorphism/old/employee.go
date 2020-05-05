package old

const (
	ENGINEER = 0
	SALESMAN = 1
	MANAGER  = 2
)

type Employee struct {
	typ         int
	monthSalary int
	commission  int
	bonus       int
}

func NewEmployee(typ int) *Employee {
	return &Employee{
		typ: typ,
	}
}

func (e *Employee) GetType() int {
	return e.typ
}

func (e *Employee) SetType(arg int) {
	e.typ = arg
}

func (e *Employee) PayAmount() int {
	switch e.typ {
	case ENGINEER:
		return e.monthSalary
	case SALESMAN:
		return e.monthSalary + e.commission
	case MANAGER:
		return e.monthSalary + e.bonus
	default:
		panic("incorrect employee")
	}
}
