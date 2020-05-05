package new

type Account struct {
	typ          *AccountType
	interestRate float64
}

func (a *Account) InterestForAmountDays(amount float64, days int) float64 {
	return a.typ.InterestForAmountDays(amount, days)
}

func (a *Account) SetInterestRate(r float64) {
	a.typ.SetInterestRate(r)
}

func (a *Account) GetInterestRate() float64 {
	return a.typ.GetInterestRate()
}

type AccountType struct {
	interestRate float64
}

func (t *AccountType) GetInterestRate() float64 {
	return t.interestRate
}

func (t *AccountType) SetInterestRate(r float64) {
	t.interestRate = r
}

func (t *AccountType) InterestForAmountDays(amount float64, days int) float64 {
	return t.GetInterestRate() * amount * float64(days) / 365
}
