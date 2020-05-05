package new

type Order struct {
	customer *Customer
}

func (o *Order) GetCustomer() *Customer {
	return o.customer
}

func (o *Order) SetCustomer(c *Customer) {
	if o.customer != nil {
		delete(o.customer.orders, o)
	}
	o.customer = c
	if o.customer != nil {
		o.customer.orders[o] = true
	}
}

type Customer struct {
	orders map[*Order]bool
}
