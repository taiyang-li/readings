package new

// 接口
type IParty interface {
	GetName() string
	GetAnnualCost() int
}

// 基类
type Party struct {
	name string
}

func (p *Party) GetName() string {
	return p.name
}

// 派生类Employee
type Employee struct {
	*Party
	annualCost int
	id         string
}

func NewEmployee(name, id string, annualCost int) *Employee {
	return &Employee{
		Party:      &Party{name},
		id:         id,
		annualCost: annualCost,
	}
}

func (e *Employee) GetAnnualCost() int {
	return e.annualCost
}

func (e *Employee) GetId() string {
	return e.id
}

// 派生类Department
type Department struct {
	*Party
	staff []IParty
}

func NewDepartment(name string) *Department {
	return &Department{
		Party: &Party{name},
	}
}

func (d *Department) GetAnnualCost() int {
	result := 0
	for i := range d.staff {
		result += d.staff[i].GetAnnualCost()
	}
	return result
}

func (d *Department) GetHeadCount() int {
	return len(d.staff)
}

func (d *Department) GetStaff() []IParty {
	return d.staff
}

func (d *Department) AddStaff(arg *Employee) {
	d.staff = append(d.staff, arg)
}
