package new

var (
	seniority      int
	monthsDisabled int
	isPartTime     bool
)

func isNotEligableForDisability() bool {
	return seniority < 2 || monthsDisabled > 12 || isPartTime
}

func disabilityAmount() float64 {
	if isNotEligableForDisability() {
		return 0
	}
	return 1
}
