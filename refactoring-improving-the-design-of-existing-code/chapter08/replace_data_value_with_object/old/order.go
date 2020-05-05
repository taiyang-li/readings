package old

type Order struct {
	customer string
}

func NewOrder(customer string) *Order {
	return &Order{
		customer: customer,
	}
}

func (o *Order) GetCustomer() string {
	return o.customer
}

func (o *Order) SetCustomer(arg string) {
	o.customer = arg
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
