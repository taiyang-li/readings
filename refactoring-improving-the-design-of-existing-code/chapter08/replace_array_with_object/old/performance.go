package old

import "strconv"

type Performance struct {
	data [3]string
}

func (p *Performance) GetName() string {
	return p.data[0]
}

func (p *Performance) GetWins() int {
	result, _ := strconv.Atoi(p.data[1])
	return result
}
func (p *Performance) SetName(arg string) {
	p.data[0] = arg
}

func (p *Performance) SetWins(arg int) {
	p.data[1] = strconv.Itoa(arg)
}
