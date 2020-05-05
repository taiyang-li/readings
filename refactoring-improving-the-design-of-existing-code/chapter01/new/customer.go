package new

import (
	"strconv"
	"strings"
)

type Customer struct {
	name    string
	rentals []*Rental
}

func NewCustomer(name string) *Customer {
	return &Customer{
		name: name,
	}
}

func (c *Customer) AddRental(arg *Rental) {
	c.rentals = append(c.rentals, arg)
}

func (c *Customer) GetName() string {
	return c.name
}

func (c *Customer) Statement() string {
	var builder strings.Builder
	builder.WriteString("Rental Record for " + c.GetName() + "\n")
	for _, each := range c.rentals {
		// show figures for this rental（显示此笔租借记录）
		builder.WriteString("\t" + each.GetMovie().GetTitle() + "\t" + strconv.FormatFloat(each.GetCharge(), 'f', -1, 64) + "\n")
	}

	// add footer lines（结尾打印）
	builder.WriteString("Amount owed is " + strconv.FormatFloat(c.GetTotalCharge(), 'f', -1, 64) + "\n")
	builder.WriteString("You earned " + strconv.Itoa(c.GetTotalFrequencyRenterPoints()) + " frequent renter points")
	return builder.String()
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
