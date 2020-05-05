package old

import "strings"

type Employee struct {
	person *Person
}

func (e *Employee) GetName() string {
	return e.person.GetName()
}

func (e *Employee) SetName(arg string) {
	return e.person.SetName(arg)
}

func (e *Employee) GetLastName() string {
	return e.person.GetLastName()
}

func (e *Employee) ToString() string {
	return "Emp:" + e.person.GetLastName()
}

type Person struct {
	name string
}

func (p *Person) GetName() string {
	return p.name
}

func (p *Person) SetName(arg string) {
	p.name = arg
}

func (p *Person) GetLastName() string {
	pos := strings.Index(p.name, " ")
	return p.name[pos+1:]
}
