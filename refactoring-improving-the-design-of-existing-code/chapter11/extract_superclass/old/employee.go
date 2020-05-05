package old

type Employee struct {
	name       string
	annualCost int
	id         string
}

func NewEmployee(name, id string, annualCost int) *Employee {
	return &Employee{
		name:       name,
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

func (e *Employee) GetName() string {
	return e.name
}

type Department struct {
	name  string
	staff []*Employee
}

func NewDepartment(name string) *Department {
	return &Department{
		name: name,
	}
}

func (d *Department) GetTotalAnnualCost() int {
	result := 0
	for i := range d.staff {
		result += d.staff[i].GetAnnualCost()
	}
	return result
}

func (d *Department) GetHeadCount() int {
	return len(d.staff)
}

func (d *Department) GetStaff() []*Employee {
	return d.staff
}

func (d *Department) AddStaff(arg *Employee) {
	d.staff = append(d.staff, arg)
}

func (d *Department) GetName() string {
	return d.name
}
