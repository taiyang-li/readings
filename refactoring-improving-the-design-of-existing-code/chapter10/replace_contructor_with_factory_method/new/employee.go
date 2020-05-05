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

func (t *Engineer) GetType() int {
	return ENGINEER
}

type Salesman struct{}

func (t *Salesman) GetType() int {
	return SALESMAN
}

type Manager struct{}

func (t *Manager) GetType() int {
	return MANAGER
}

func CreateEmployee(typ int) Employee {
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
