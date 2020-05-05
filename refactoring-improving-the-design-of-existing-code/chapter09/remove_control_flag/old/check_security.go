package old

func sendAlert() {}
func CheckSecurity(people []string) {
	found := false
	for idx := range people {
		if !found {
			if people[idx] == "Don" {
				sendAlert()
				found = true
			}
			if people[idx] == "John" {
				sendAlert()
				found = true
			}
		}
	}
}
