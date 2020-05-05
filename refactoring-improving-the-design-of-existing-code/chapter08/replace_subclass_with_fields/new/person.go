package new

type Person struct {
	isMale bool
	code   byte
}

func (p *Person) GetCode() byte {
	return p.code
}

func (p *Person) IsMale() bool {
	return p.isMale
}

func CreateMale() *Person {
	return &Person{
		isMale: true,
		code:   'M',
	}
}

func CreateFemale() *Person {
	return &Person{
		isMale: false,
		code:   'F',
	}
}
