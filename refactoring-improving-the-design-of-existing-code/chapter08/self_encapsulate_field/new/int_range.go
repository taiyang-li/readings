package new

type IntRange struct {
	low  int
	high int
}

func (r *IntRange) Includes(arg int) bool {
	return arg >= r.low && arg <= r.high
}

func (r *IntRange) Grow(factor int) {
	r.high *= factor
}

func (r *IntRange) SetLow(arg int) {
	r.low = arg
}

func (r *IntRange) SetHigh(arg int) {
	r.high = arg
}

func (r *IntRange) GetLow() int {
	return r.low
}

func (r *IntRange) GetHigh() int {
	return r.high
}

func NewIntRange(low, high int) *IntRange {
	return &IntRange{
		low:  low,
		high: high,
	}
}

type CappedRange struct {
	IntRange

	cap int
}

func (r *CappedRange) GetCap() int {
	return r.cap
}

func (r *CappedRange) GetHigh() int {
	if r.IntRange.GetHigh() > r.GetCap() {
		return r.IntRange.GetHigh()
	} else {
		return r.GetCap()
	}
}
