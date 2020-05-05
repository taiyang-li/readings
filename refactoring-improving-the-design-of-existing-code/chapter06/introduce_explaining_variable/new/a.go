package new

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
	isMacOs := strings.Contains(strings.ToUpper(platform), "MAC")
	isIEBrowser := strings.Contains(strings.ToUpper(browser), "IE")
	if isMacOs && isIEBrowser && wasInitialized() && resize > 0 {
		fmt.Println("xxx")
	}
}

func wasInitialized() bool {
	return true
}
