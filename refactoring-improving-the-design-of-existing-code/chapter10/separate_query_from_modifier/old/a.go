pacakge old

func sendAlert() { }

func foundMiscreant(people []string) string {
	for i := range people {
		if people[i] == "Don" {
			sendAlert()
			return "Don"
		}
		if people[i] == "John" {
			sendAlert()
			return "John"
		}
	}
	return ""
}

func someLaterCode(arg string) {}

func CheckSecurity(people []string) {
	found := foundMiscreant(people)
	someLaterCode(people)
}