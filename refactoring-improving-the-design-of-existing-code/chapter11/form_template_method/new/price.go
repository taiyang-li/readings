package new

type Price interface {
	GetPriceCode() int
	GetCharge(daysRented int) float64
	GetFrequentRenterPoints(daysRented int) int
}

func CreatePrice(priceCode int) Price {
	switch priceCode {
	case CHILDRENS:
		return &ChildrensPrice{}
	case NEW_RELEASE:
		return &NewReleasePrice{}
	case REGULAR:
		return &RegularPrice{}
	default:
		return nil
	}
}

type ChildrensPrice struct{}

func (p *ChildrensPrice) GetPriceCode() int {
	return CHILDRENS
}
func (p *ChildrensPrice) GetFrequentRenterPoints(daysRented int) int {
	return 1
}

func (p *ChildrensPrice) GetCharge(daysRented int) float64 {
	result := 1.5
	if daysRented > 3 {
		result += float64(daysRented-3) * 1.5
	}
	return result
}

type NewReleasePrice struct{}

func (p *NewReleasePrice) GetPriceCode() int {
	return NEW_RELEASE
}

func (p *NewReleasePrice) GetCharge(daysRented int) float64 {
	return float64(daysRented) * 3.0
}

func (p *NewReleasePrice) GetFrequentRenterPoints(daysRented int) int {
	if daysRented > 1 {
		return 2
	} else {
		return 1
	}
}

type RegularPrice struct{}

func (p *RegularPrice) GetPriceCode() int {
	return REGULAR
}

func (p *RegularPrice) GetCharge(daysRented int) float64 {
	result := 2.0
	if daysRented > 2 {
		result += float64(daysRented-2) * 1.5
	}
	return result
}

func (p *RegularPrice) GetFrequentRenterPoints(daysRented int) int {
	return 1
}
