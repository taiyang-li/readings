package new

type Employee struct {
	name string
	id   string
}

func NewEmployee(name, id string) *Employee {
	return &Employee{
		name: name,
		id:   id,
	}
}

type Manager struct {
	*Employee
	grade int
}

func NewManager(name, id string, grade int) *Manager {
	return &Manager{
		Employee: NewEmployee(name, id),
		grade:    grade,
	}
}
