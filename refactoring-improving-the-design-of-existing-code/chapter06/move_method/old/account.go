package old

type Account struct {
	typ           *AccountType
	daysOverdrawn int
}

func (a *Account) OverdraftCharge() float64 {
	if a.typ.IsPremium() {
		result := 10.0
		if a.daysOverdrawn > 7 {
			result += float64(a.daysOverdrawn-7) * 0.853
		}
		return result
	} else {
		return float64(a.daysOverdrawn) * 1.75
	}
}

type AccountType struct {
}

func (t *AccountType) IsPremium() bool {
	return true
}
