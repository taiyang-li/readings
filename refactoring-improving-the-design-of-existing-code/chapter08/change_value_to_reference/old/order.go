package old

type Order struct {
	customer *Customer
}


func NewOrder(customer string) *Order {
	o := &Order{}
	o.SetCustomer(customer)
	return o
}

func (o *Order) GetCustomer() string {
	return o.customer.GetName()
}

func (o *Order) SetCustomer(arg string) {
	o.customer = &Customer{
		name: arg,
	}
}

type Customer struct {
	name string
}

func (c *Customer) GetName() string {
	return c.name
}

func NewCustomer(name string) *Customer {
	return &Customer{
		name: name,
	}
} 

func NumberOfOrdersFor(orders []*Order, customer string) int {
	result := 0
	for idx := range orders {
		if orders[idx].GetCustomer() == customer {
			result++
		}
	}
	return result
}