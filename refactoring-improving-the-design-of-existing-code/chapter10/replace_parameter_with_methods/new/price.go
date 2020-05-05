package new

var (
	quantity  float64
	itemPrice float64
)

func getBasePrice() float64 {
	return quantity * itemPrice
}

func getDiscountLevel() int {
	if quantity > 100 {
		return 2
	} else {
		return 1
	}
}

func GetPrice() float64 {
	return discountedPrice()
}

func discountedPrice() float64 {
	basePrice := getBasePrice()
	discountLevel := getDiscountLevel()
	if discountLevel == 2 {
		return basePrice * 0.1
	} else {
		return basePrice * 0.05
	}
}
