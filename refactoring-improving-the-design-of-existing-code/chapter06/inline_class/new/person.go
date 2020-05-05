package new

type Person struct {
	name            string
	officeTelephone *TelephoneNumber
}

func (p *Person) GetName() string {
	return p.name
}

func (p *Person) GetOfficeTelephone() *TelephoneNumber {
	return p.officeTelephone
}

func (p *Person) GetAreaCode() string {
	return p.officeTelephone.GetAreaCode()
}

func (p *Person) SetAreaCode(arg string) {
	p.officeTelephone.SetAreaCode(arg)
}

type TelephoneNumber struct {
	areaCode string
	number   string
}

func (n *TelephoneNumber) GetAreaCode() string {
	return n.areaCode
}

func (n *TelephoneNumber) SetAreaCode(arg string) {
	n.areaCode = arg
}

func (n *TelephoneNumber) GetNumber() string {
	return n.number
}

func (n *TelephoneNumber) SetNumber(arg string) {
	n.number = arg
}
