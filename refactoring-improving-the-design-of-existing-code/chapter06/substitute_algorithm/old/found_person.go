package old

func FoundPerson(people []string) string {
	for idx := range people {
		if people[idx] == "Don" {
			return "Don"
		}
		if people[idx] == "John" {
			return "John"
		}
		if people[idx] == "Kent" {
			return "Kent"
		}
	}
	return ""
}
