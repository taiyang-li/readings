package new

const (
	ENGINEER = 0
	SALESMAN = 1
	MANAGER  = 2
)

type Employee interface {
	GetType() int
}

type Engineer struct{}

func (e *Engineer) GetType() int {
	return ENGINEER
}

func CreateEngineer() *Engineer {
	return &Engineer{}
}

type Salesman struct{}

func (s *Salesman) GetType() int {
	return SALESMAN
}

func CreateSalesman() *Salesman {
	return &Salesman{}
}

type Manager struct{}

func (m *Manager) GetType() int {
	return MANAGER
}

func CreateManager() *Manager {
	return &Manager{}
}
