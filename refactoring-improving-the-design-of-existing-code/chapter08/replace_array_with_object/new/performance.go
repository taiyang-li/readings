package new

type Performance struct {
	name string
	wins int
}

func (p *Performance) GetName() string {
	return p.name
}

func (p *Performance) GetWins() int {
	return p.wins
}
func (p *Performance) SetName(arg string) {
	p.name = arg
}

func (p *Performance) SetWins(arg int) {
	p.wins = arg
}
