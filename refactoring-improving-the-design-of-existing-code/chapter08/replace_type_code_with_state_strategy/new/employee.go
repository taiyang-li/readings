package new

const (
	ENGINEER = 0
	SALESMAN = 1
	MANAGER  = 2
)

type EmployeeType interface {
	GetType() int
	PayAmount(monthSalary, commission, bonus int) int
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

func (t *EngineerType) PayAmount(monthSalary, commission, bonus int) int {
	return monthSalary
}

type SalesmanType struct{}

func (t *SalesmanType) GetType() int {
	return SALESMAN
}

func (t *SalesmanType) PayAmount(monthSalary, commission, bonus int) int {
	return monthSalary + commission
}

type ManagerType struct{}

func (t *ManagerType) GetType() int {
	return MANAGER
}

func (t *ManagerType) PayAmount(monthSalary, commission, bonus int) int {
	return monthSalary + bonus
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

func (e *Employee) GetType() int {
	return e.typ.GetType()
}

func (e *Employee) SetType(arg int) {
	e.typ = Create(arg)
}

func (e *Employee) PayAmount() int {
	return e.typ.PayAmount(e.monthSalary, e.commission, e.bonus)
}
