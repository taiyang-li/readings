package old

import "fmt"

var (
	height int
	width  int
)

func a() {
	tmp := 2 * (height + width)
	fmt.Println(tmp)

	tmp = height * width
	fmt.Println(tmp)
}
