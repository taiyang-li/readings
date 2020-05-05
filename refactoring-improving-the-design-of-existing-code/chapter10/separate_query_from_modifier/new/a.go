pacakge new

func doSendAlert() { }

func foundPerson(people []string) string {
	for i := range people {
		if people[i] == "Don" {
			return "Don"
		}
		if people[i] == "John" {
			return "John"
		}
	}
	return ""
}

func sendAlert(people []string) {
	found := foundPerson(people)
	if found != "" {
		doSendAlert()
	}
}

func someLaterCode(arg string) {}

func CheckSecurity(people []string) {
	sendAlert(people)
	someLaterCode(people)
}