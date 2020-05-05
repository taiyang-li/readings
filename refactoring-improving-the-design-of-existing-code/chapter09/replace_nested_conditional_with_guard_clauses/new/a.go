package new

var (
	isDead      bool
	isSeparated bool
	isRetired   bool
)

func deadAmount() float64 {
	return 0.0
}

func separatedAmount() float64 {
	return 0.0
}

func retiredAmount() float64 {
	return 0.0
}

func normalPayAmount() float64 {
	return 0.0
}

func GetPayAmount() float64 {
	if isDead {
		return deadAmount()
	}
	if isSeparated {
		return separatedAmount()
	}
	if isRetired {
		return retiredAmount()
	}
	return normalPayAmount()
}
