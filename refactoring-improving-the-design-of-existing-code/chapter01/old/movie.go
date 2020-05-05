package old

var (
	CHILDRENS   = 2
	REGULAR     = 0
	NEW_RELEASE = 1
)

type Movie struct {
	title     string
	priceCode int
}

func NewMoive(title string, priceCode int) *Movie {
	return &Movie{
		title:     title,
		priceCode: priceCode,
	}
}

func (m *Movie) GetPriceCode() int {
	return m.priceCode
}

func (m *Movie) SetPriceCode(priceCode int) {
	m.priceCode = priceCode
}

func (m *Movie) GetTitle() string {
	return m.title
}
