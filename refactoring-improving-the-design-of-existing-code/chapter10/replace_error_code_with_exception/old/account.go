package old

type Account struct {
	balance int
}

func (a *Account) Withdraw(amount int) int {
	if amount > a.balance {
		return -1
	} else {
		a.balance -= amount
		return 0
	}
}
