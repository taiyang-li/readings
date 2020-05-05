package new

var (
	price int
)

func isSpecialDeal() bool {
	return true
}

func send() {
}

func main() {
	var total float64
	if isSpecialDeal() {
		total = float64(price) * 0.95
	} else {
		total = float64(price) * 0.98
	}
	send()

	_ = total
}
