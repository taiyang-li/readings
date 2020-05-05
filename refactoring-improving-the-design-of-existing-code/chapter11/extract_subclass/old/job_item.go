package old

type JobItem struct {
	unitPrice int
	quantity  int
	isLabor   bool
	employee  *Employee
}

func NewJobItem(unitPrice, quantity int, isLabor bool, employee *Employee) *JobItem {
	return &JobItem{
		unitPrice: unitPrice,
		quantity:  quantity,
		isLabor:   isLabor,
		employee:  employee,
	}
}

func (i *JobItem) GetUnitPrice() int {
	return i.unitPrice
}

func (i *JobItem) GetQuantity() int {
	return i.quantity
}

func (i *JobItem) GetEmployee() *Employee {
	return i.employee
}

func (i *JobItem) GetTotalPrice() int {
	return i.GetUnitPrice() * i.quantity
}

type Employee struct {
	rate int
}

func NewEmployee(rate int) *Employee {
	return &Employee{
		rate: rate,
	}
}

func (e *Employee) GetRate() int {
	return e.rate
}
