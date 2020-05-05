package old

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
	result := 0.0
	if isDead {
		result = deadAmount()
	} else {
		if isSeparated {
			result = separatedAmount()
		} else {
			if isRetired {
				result = retiredAmount()
			} else {
				result = normalPayAmount()
			}
		}
	}
	return result
}
