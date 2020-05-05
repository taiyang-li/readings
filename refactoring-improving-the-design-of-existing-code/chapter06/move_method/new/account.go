package new

type Account struct {
	typ           *AccountType
	daysOverdrawn int
}

func (a *Account) OverdraftCharge() float64 {
	return a.typ.overdraftCharge(a.daysOverdrawn)
}

type AccountType struct{}

func (t *AccountType) IsPremium() bool {
	return true
}

func (t *AccountType) overdraftCharge(daysOverdrawn int) float64 {
	if t.IsPremium() {
		result := 10.0
		if daysOverdrawn > 7 {
			result += float64(daysOverdrawn-7) * 0.853
		}
		return result
	} else {
		return float64(daysOverdrawn) * 1.75
	}
}
