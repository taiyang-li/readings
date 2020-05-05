package old

var (
	anOrder Order
)

type Order struct {
}

func (o Order) BasePrice() int {
	return 1
}

func BasePriceTooHigh() bool {
	basePrice := anOrder.BasePrice()
	return basePrice > 1000
}
