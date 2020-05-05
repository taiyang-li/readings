package new

type Customer struct {
	name      string
	rentals   []*Rental
	statement *StatementTemplate
}

func NewCustomer(name string) *Customer {
	return &Customer{
		name:      name,
		statement: NewStatementTemplate(),
	}
}

func (c *Customer) GetRentals() []*Rental {
	return c.rentals
}
func (c *Customer) AddRental(arg *Rental) {
	c.rentals = append(c.rentals, arg)
}

func (c *Customer) GetName() string {
	return c.name
}

func (c *Customer) Statement(typ string) string {
	c.statement.SetType(typ)
	return c.statement.Value()
}

func (c *Customer) amountFor(rental *Rental) float64 {
	return rental.GetCharge()
}

func (c *Customer) GetTotalCharge() float64 {
	result := 0.0
	for _, each := range c.rentals {
		result += each.GetCharge()
	}
	return result
}

func (c *Customer) GetTotalFrequencyRenterPoints() int {
	result := 0
	for _, each := range c.rentals {
		result += each.GetFrequentRenterPoints()
	}
	return result
}
