package old

var (
	quantity  float64
	itemPrice float64
)

func GetPrice() float64 {
	basePrice := quantity * itemPrice
	discountLevel := 0
	if quantity > 100 {
		discountLevel = 2
	} else {
		discountLevel = 1
	}

	finalPrice := discountedPrice(basePrice, discountLevel)
	return finalPrice
}

func discountedPrice(basePrice float64, discountLevel int) float64 {
	if discountLevel == 2 {
		return basePrice * 0.1
	} else {
		return basePrice * 0.05
	}
}
