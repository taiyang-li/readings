package old

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
