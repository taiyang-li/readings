package new

var (
	anOrder Order
)

type Order struct {
}

func (o Order) BasePrice() int {
	return 1
}

func BasePriceTooHigh() bool {
	return anOrder.BasePrice() > 1000
}
