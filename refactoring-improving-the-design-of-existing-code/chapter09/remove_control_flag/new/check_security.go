package new

func sendAlert() {}

func CheckSecurity(people []string) {
	found := ""
	for idx := range people {
		if people[idx] == "Don" {
			found = "Don"
			break
		}
		if people[idx] == "John" {
			found = "John"
			break
		}
	}
	if found != "" {
		sendAlert()
	}
}
