opackage new

const (
	ENGINEER = 0
	SALESMAN = 1
	MANAGER  = 2
)

type EmployeeType interface {
	GetType() int
	PayAmount(e *Employee) int
}

func Create(typ int) EmployeeType {
	switch typ {
	case ENGINEER:
		return &EngineerType{}
	case SALESMAN:
		return &SalesmanType{}
	case MANAGER:
		return &ManagerType{}
	default:
		panic("invalid type")
	}
}

type EngineerType struct{}

func (t *EngineerType) GetType() int {
	return ENGINEER
}

func (t *EngineerType) PayAmount(e *Employee) int {
	return e.GetMonthSalary()
}

type SalesmanType struct{}

func (t *SalesmanType) GetType() int {
	return SALESMAN
}

func (t *SalesmanType) PayAmount(e *Employee) int {
	return e.GetMonthSalary() + e.GetCommission()
}

type ManagerType struct{}

func (t *ManagerType) GetType() int {
	return MANAGER
}

func (t *ManagerType) PayAmount(e *Employee) int {
	return e.GetMonthSalary() + e.GetBonus()
}

type Employee struct {
	typ         EmployeeType
	monthSalary int
	commission  int
	bonus       int
}

func NewEmployee(typ int) *Employee {
	return &Employee{
		typ: Create(typ),
	}
}

func (e *Employee) GetMonthSalary() int {
	return e.monthSalary
}

func (e *Employee) GetCommission() int {
	return e.commission
}

func (e *Employee) GetBonus() int {
	return e.bonus
}

func (e *Employee) GetType() int {
	return e.typ.GetType()
}

func (e *Employee) SetType(arg int) {
	e.typ = Create(arg)
}

func (e *Employee) PayAmount() int {
	return e.typ.PayAmount(e)
}
