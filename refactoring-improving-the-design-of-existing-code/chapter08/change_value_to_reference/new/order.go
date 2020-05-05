package new

var (
	instances = map[string]*customer{}
)

func init() {
	a := customer{"a"}
	a.store()

	b := customer{"b"}
	b.store()

	c := customer{"c"}
	c.store()
}

type Order struct {
	customer *customer
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
	o.customer = &customer{
		name: arg,
	}
}

type customer struct {
	name string
}

func (c *customer) GetName() string {
	return c.name
}

func (c *customer) store() {
	instances[c.name] = c
}

func getNamed(name string) *customer {
	return instances[name]
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
