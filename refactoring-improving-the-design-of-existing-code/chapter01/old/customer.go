package old

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
	totalAmount := 0.0        // 总消费金。
	frequentRenterPoints := 0 // 常客积点
	var builder strings.Builder
	builder.WriteString("Rental Record for " + c.GetName() + "\n")

	// TODO 函数太长：Extract Method
	// TODO 金额计算和积分计算都之和Rental相关：Move Method
	// TODO 临时变量thisAmount和frequentRenterPoints使用过多：Replace Temp With Query
	// TODO switch语句：Replace Type Code With State/Strategy和Replace Conditional with Polymorphism
	for _, each := range c.rentals {
		thisAmount := 0.0
		// determine amounts for each line
		switch each.GetMovie().GetPriceCode() { // 取得影片出租价格
		case REGULAR: // 普通片
			thisAmount += 2
			if each.GetDaysRented() > 2 {
				thisAmount += float64(each.GetDaysRented()-2) * 1.5
			}
		case NEW_RELEASE: // 新片
			thisAmount += float64(each.GetDaysRented()) * 3.0
		case CHILDRENS: // 儿童。
			thisAmount += 1.5
			if each.GetDaysRented() > 3 {
				thisAmount += float64(each.GetDaysRented()-3) * 1.5
			}
		}

		// add frequent renter points （累计常客积点。
		frequentRenterPoints++
		// add bonus for a two day new release rental
		if (each.GetMovie().GetPriceCode() == NEW_RELEASE) && each.GetDaysRented() > 1 {
			frequentRenterPoints++
		}

		// show figures for this rental（显示此笔租借记录）
		builder.WriteString("\t" + each.GetMovie().GetTitle() + "\t" + strconv.FormatFloat(thisAmount, 'f', -1, 64) + "\n")
		totalAmount += thisAmount
	}

	// add footer lines（结尾打印）
	// TODO 使用临时变量totalAmount,
	builder.WriteString("Amount owed is " + strconv.FormatFloat(totalAmount, 'f', -1, 64) + "\n")
	builder.WriteString("You earned " + strconv.Itoa(frequentRenterPoints) + " frequent renter points")
	return builder.String()
}
