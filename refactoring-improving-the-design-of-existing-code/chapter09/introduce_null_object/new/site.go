package old

type Site struct {
	customer ICustomer
}

func (s *Site) GetCustomer() ICustomer {
	return s.customer
}

func (s *Site) SetCustomer(arg ICustomer) {
	if arg == nil {
		s.customer = NewNullCustomer()
	} else {
		s.customer = arg
	}
}

type ICustomer interface {
	GetName() string
	GetPlan() *BillingPlan
	GetHistory() IPaymentHistory
}

type Customer struct{}

func NewCustomer() *Customer {
	return &Customer{}
}

func (c *Customer) GetName() string {
	return "name"
}

func (c *Customer) GetPlan() *BillingPlan {
	return &BillingPlan{}
}

func (c *Customer) GetHistory() IPaymentHistory {
	return NewPaymentHistory()
}

type NullCustomer struct{}

func NewNullCustomer() *NullCustomer {
	return &NullCustomer{}
}
func (c *NullCustomer) GetName() string {
	return "occupant"
}

func (c *NullCustomer) GetPlan() *BillingPlan {
	return BasicBillingPlan()
}

func (c *NullCustomer) GetHistory() IPaymentHistory {
	return NewNullPaymentHistory()
}

type IPaymentHistory interface {
	GetWeeksDelinquentInLastYear() int
}

type PaymentHistory struct{}

func NewPaymentHistory() *PaymentHistory {
	return &PaymentHistory{}
}

func (h *PaymentHistory) GetWeeksDelinquentInLastYear() int {
	return 1
}

type NullPaymentHistory struct{}

func NewNullPaymentHistory() *NullPaymentHistory {
	return &NullPaymentHistory{}
}

func (h *NullPaymentHistory) GetWeeksDelinquentInLastYear() int {
	return 0
}

type BillingPlan struct{}

func BasicBillingPlan() *BillingPlan {
	return &BillingPlan{}
}

func Example() {
	var site Site
	customer := site.GetCustomer()
	plan := customer.GetPlan()
	customerName := customer.GetName()
	weeksDelinquent := customer.GetHistory().GetWeeksDelinquentInLastYear()

	_ = plan
	_ = customerName
	_ = weeksDelinquent
}
