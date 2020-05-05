package new

type Account struct {
	id string
}

func NewAccount(id string) *Account {
	return &Account{
		id: id,
	}
}
