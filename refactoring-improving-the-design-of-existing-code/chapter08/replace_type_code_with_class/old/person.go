package old

var (
	O  = 0
	A  = 1
	B  = 2
	AB = 3
)

type Person struct {
	bloodGroup int
}

func NewPerson(bloodGroup int) *Person {
	return &Person{
		bloodGroup: bloodGroup,
	}
}

func (p *Person) GetBloodGroup() int {
	return p.bloodGroup
}

func (p *Person) SetBloodGroup(arg int) {
	p.bloodGroup = arg
}
