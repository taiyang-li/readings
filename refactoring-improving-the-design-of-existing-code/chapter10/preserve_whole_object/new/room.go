package new

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
	return plan.WithinRange(r.daysTempRange())
}

type HeatingPlan struct {
	tempRange *TempRange
}

func (p *HeatingPlan) WithinRange(r *TempRange) bool {
	return r.Low >= p.tempRange.Low && r.High <= p.tempRange.High
}
