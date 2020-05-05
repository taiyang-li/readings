package old

type Employee struct {
	name string
	id   string
}

type Manager struct {
	*Employee
	grade int
}

func NewManager(name, id string, grade int) *Manager {
	return &Manager{
		Employee: &Employee{
			name: name,
			id:   id,
		},
		grade: grade,
	}
}
