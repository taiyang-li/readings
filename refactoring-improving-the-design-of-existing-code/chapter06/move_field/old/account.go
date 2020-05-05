package old

type Account struct {
	typ          *AccountType
	interestRate float64
}

func (a *Account) InterestForAmountDays(amount float64, days int) float64 {
	return a.interestRate * amount * float64(days) / 365
}

type AccountType struct{}
