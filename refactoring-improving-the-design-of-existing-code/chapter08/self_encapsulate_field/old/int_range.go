package old

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

func NewIntRange(low, high int) *IntRange {
	return &IntRange{
		low:  low,
		high: high,
	}
}
