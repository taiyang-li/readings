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

type Salesman struct{}

func (s *Salesman) GetType() int {
	return SALESMAN
}

type Manager struct{}

func (m *Manager) GetType() int {
	return MANAGER
}

func Create(typ int) Employee {
	switch typ {
	case ENGINEER:
		return &Engineer{}
	case SALESMAN:
		return &Salesman{}
	case MANAGER:
		return &Manager{}
	default:
		panic("invalid type")
	}
}
