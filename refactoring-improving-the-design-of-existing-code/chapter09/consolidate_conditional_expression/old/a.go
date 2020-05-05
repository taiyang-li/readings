package old

var (
	seniority      int
	monthsDisabled int
	isPartTime     bool
)

func disabilityAmount() float64 {
	if seniority < 2 {
		return 0
	}
	if monthsDisabled > 12 {
		return 0
	}
	if isPartTime {
		return 0
	}
	return 1
}
