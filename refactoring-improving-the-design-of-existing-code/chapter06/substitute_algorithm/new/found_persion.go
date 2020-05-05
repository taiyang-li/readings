package new

func FoundPerson(people []string) string {
	candidates := []string{"Don", "John", "Kent"}
	for idx := range people {
		if contains(candidates, people[idx]) {
			return people[idx]
		}
	}
	return ""
}

func contains(strs []string, target string) bool {
	for idx := range strs {
		if strs[idx] == target {
			return true
		}
	}
	return false
}
