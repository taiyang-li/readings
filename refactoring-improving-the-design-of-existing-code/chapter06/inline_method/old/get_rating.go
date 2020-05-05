package old

var (
	numberOfLateDeliveries int
)

func GetRating() int {
	if moreThanFiveLateDeiliveries() {
		return 2
	} else {
		return 1
	}
}

func moreThanFiveLateDeiliveries() bool {
	return numberOfLateDeliveries > 5
}
