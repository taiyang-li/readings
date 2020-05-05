package new

import "fmt"

var (
	ErrBalanceNotEnough = fmt.Errorf("balance not enough")
)

type Account struct {
	balance int
}

func (a *Account) Withdraw(amount int) error {
	if amount > a.balance {
		return ErrBalanceNotEnough
	}
	a.balance -= amount
	return nil
}
