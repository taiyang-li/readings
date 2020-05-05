package new

var (
	O  = NewBloodGroup(0)
	A  = NewBloodGroup(1)
	B  = NewBloodGroup(2)
	AB = NewBloodGroup(3)
)

type BloodGroup struct {
	code int
}

func NewBloodGroup(code int) *BloodGroup {
	return &BloodGroup{
		code: code,
	}
}

func (g *BloodGroup) Code() int {
	return g.code
}

type Person struct {
	bloodGroup *BloodGroup
}

func NewPerson(bloodGroup *BloodGroup) *Person {
	return &Person{
		bloodGroup: bloodGroup,
	}
}

func (p *Person) GetBloodGroup() *BloodGroup {
	return p.bloodGroup
}

func (p *Person) SetBloodGroup(arg *BloodGroup) {
	p.bloodGroup = arg
}
