package new

var (
	numberOfLateDeliveries int
)

func GetRating() int {
	if numberOfLateDeliveries > 5 {
		return 2
	} else {
		return 1
	}
}
