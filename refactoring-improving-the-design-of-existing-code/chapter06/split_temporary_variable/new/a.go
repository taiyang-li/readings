package new

import "fmt"

var (
	height int
	width  int
)

func a() {
	perimeter := 2 * (height + width)
	fmt.Println(perimeter)

	area := height * width
	fmt.Println(area)
}
