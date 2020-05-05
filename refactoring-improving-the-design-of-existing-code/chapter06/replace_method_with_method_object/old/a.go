package old

type Account struct {
}

func (a *Account) Gamma(inputVal1, quantity, yearToDate int) int {
	importantValue1 := (inputVal1 * quantity) * a.delta()
	importantValue2 := (inputVal1 * yearToDate) + 100
	if yearToDate-importantValue1 > 100 {
		importantValue2 -= 20
	}
	importantValue3 := importantValue2 * 7
	return importantValue3 - 2*importantValue1
}

func (a *Account) delta() int {
	return 0
}
