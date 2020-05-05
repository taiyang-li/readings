package old

type Person interface {
	IsMale() bool
	GetCode() byte
}

type Male struct{}

func (m *Male) IsMale() bool {
	return true
}

func (m *Male) GetCode() byte {
	return 'M'
}

type Female struct{}

func (m *Female) IsMale() bool {
	return false
}

func (m *Female) GetCode() byte {
	return 'F'
}

func CreateMale() Person {
	return &Male{}
}

func CreateFemale() Person {
	return &Female{}
}
