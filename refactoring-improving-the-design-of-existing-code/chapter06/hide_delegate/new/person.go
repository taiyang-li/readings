package new

type Person struct {
	department *Department
}

func (p *Person) GetDepartment() *Department {
	return p.department
}

func (p *Person) GetManager() *Person {
	return p.department.GetManager()
}

func (p *Person) SetDepartment(arg *Department) {
	p.department = arg
}

type Department struct {
	chargeCode string
	manager    *Person
}

func NewDepartment(manager *Person) *Department {
	return &Department{
		manager: manager,
	}
}

func (p *Department) GetManager() *Person {
	return p.manager
}

func GetManager(p *Person) *Person {
	return p.GetManager()
}
