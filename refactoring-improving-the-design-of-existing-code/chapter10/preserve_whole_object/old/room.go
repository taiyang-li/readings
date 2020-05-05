package old

type TempRange struct {
	Low  int
	High int
}

type Room struct {
}

func (r *Room) daysTempRange() *TempRange {
	return &TempRange{}
}

func (r *Room) WithinPlan(plan *HeatingPlan) bool {
	low := r.daysTempRange().Low
	high := r.daysTempRange().High
	return plan.WithinRange(low, high)
}

type HeatingPlan struct {
	tempRange *TempRange
}

func (p *HeatingPlan) WithinRange(low, high int) bool {
	return low >= p.tempRange.Low && high <= p.tempRange.High
}
