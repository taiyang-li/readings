package old

type Site struct {
	customer *Customer
}

func (s *Site) GetCustomer() *Customer {
	return s.customer
}

type Customer struct {
}

func (c *Customer) GetName() string {
	return "name"
}

func (c *Customer) GetPlan() *BillingPlan {
	return &BillingPlan{}
}

func (c *Customer) GetHistory() *PaymentHistory {
	return &PaymentHistory{}
}

type PaymentHistory struct{}

func (h *PaymentHistory) GetWeeksDelinquentInLastYear() int {
	return 0
}

type BillingPlan struct{}

func BasicBillingPlan() *BillingPlan {
	return &BillingPlan{}
}

func Example() {
	var site Site
	customer := site.GetCustomer()

	var plan *BillingPlan
	if customer == nil {
		plan = BasicBillingPlan()
	} else {
		plan = customer.GetPlan()
	}
	_ = plan

	var customerName string
	if customer == nil {
		customerName = "occupant"
	} else {
		customerName = customer.GetName()
	}
	_ = customerName

	var weeksDelinquent int
	if customer == nil {
		weeksDelinquent = 0
	} else {
		weeksDelinquent = customer.GetHistory().GetWeeksDelinquentInLastYear()
	}
	_ = weeksDelinquent
}
