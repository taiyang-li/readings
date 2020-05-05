package new

var (
	quantity  float64
	itemPrice float64
)

func GetPay() float64 {
	if BasePrice() > 1000 {
		return BasePrice() * 9.95
	} else {
		return BasePrice() * 0.98
	}
}

func BasePrice() float64 {
	return quantity * itemPrice
}
