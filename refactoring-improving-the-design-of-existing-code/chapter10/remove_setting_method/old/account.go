package old

type Account struct {
	id string
}

func NewAccount(id string) *Account {
	return &Account{
		id: id,
	}
}

func (a *Account) SetId(arg string) {
	a.id = arg
}
