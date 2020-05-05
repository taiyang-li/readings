package new

var (
	CHILDRENS   = 2
	REGULAR     = 0
	NEW_RELEASE = 1
)

type Movie struct {
	title string
	price Price
}

func NewMoive(title string, priceCode int) *Movie {
	m := &Movie{
		title: title,
	}
	m.SetPriceCode(priceCode)
	return m
}

func (m *Movie) GetPriceCode() int {
	return m.price.GetPriceCode()
}

func (m *Movie) SetPriceCode(priceCode int) {
	m.price = CreatePrice(priceCode)
}

func (m *Movie) GetTitle() string {
	return m.title
}

func (m *Movie) GetCharge(daysRented int) float64 {
	return m.price.GetCharge(daysRented)
}

func (m *Movie) GetFrequentRenterPoints(daysRented int) int {
	return m.price.GetFrequentRenterPoints(daysRented)
}
