package old

import (
	"fmt"
	"strings"
)

var (
	platform string
	browser  string
	resize   int
)

func a() {
	if strings.Contains(strings.ToUpper(platform), "MAC") &&
		strings.Contains(strings.ToUpper(browser), "IE") &&
		wasInitialized() && resize > 0 {
		fmt.Println("xxx")
	}
}

func wasInitialized() bool {
	return true
}
