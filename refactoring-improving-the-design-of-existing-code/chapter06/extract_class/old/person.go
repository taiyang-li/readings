package old

type Person struct {
	name           string
	officeAreaCode string
	officeNumber   string
}

func (p *Person) GetName() string {
	return p.name
}

func (p *Person) GetOfficeAreaCode() string {
	return p.officeAreaCode
}

func (p *Person) SetOfficeAreaCode(arg string) {
	p.officeAreaCode = arg
}

func (p *Person) GetOfficeNumber() string {
	return p.officeNumber
}

func (p *Person) SetOfficeNumber(arg string) {
	p.officeNumber = arg
}
