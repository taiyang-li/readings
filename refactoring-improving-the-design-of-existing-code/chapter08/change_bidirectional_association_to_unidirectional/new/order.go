package new

type Order struct {
	customer *Customer
}

func (o *Order) GetCustomer() *Customer {
	return o.customer
}

func (o *Order) SetCustomer(c *Customer) {
	o.customer = c
}

type Customer struct {
	// orders map[*Order]bool
}
