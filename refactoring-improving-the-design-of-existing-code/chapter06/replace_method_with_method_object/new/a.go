package new

type Account struct {
}

func (a *Account) delta() int {
	return 0
}

func (a *Account) Gamma(inputVal, quantity, yearToDate int) int {
	return NewGamma(a, inputVal, quantity, yearToDate).Compute()
}

type Gamma struct {
	account         *Account
	inputVal        int
	quantity        int
	yearToDate      int
	importantValue1 int
	importantValue2 int
	importantValue3 int
}

func NewGamma(source *Account, inputVal, quantity, yearToDate int) *Gamma {
	return &Gamma{
		account:    source,
		inputVal:   inputVal,
		quantity:   quantity,
		yearToDate: yearToDate,
	}
}

func (g *Gamma) Compute() int {
	g.importantValue1 = (g.inputVal * g.quantity) * g.account.delta()
	g.importantValue2 = (g.inputVal * g.yearToDate) + 100
	g.importantThing()
	g.importantValue3 = g.importantValue2 * 7
	return g.importantValue3 - 2*g.importantValue1
}

func (g *Gamma) importantThing() {
	if g.yearToDate-g.importantValue1 > 100 {
		g.importantValue2 -= 20
	}
}
