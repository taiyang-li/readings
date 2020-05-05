package old

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
