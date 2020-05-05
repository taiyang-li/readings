package old

var (
	quantity  float64
	itemPrice float64
)

func GetPay() float64 {
	basePrice := quantity * itemPrice
	if basePrice > 1000 {
		return basePrice * 9.95
	} else {
		return basePrice * 0.98
	}
}
