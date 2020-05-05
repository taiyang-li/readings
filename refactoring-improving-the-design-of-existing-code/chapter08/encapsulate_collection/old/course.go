package old

type Course struct {
	name       string
	isAdvanced bool
}

func (c *Course) IsAdvanced() bool {
	return c.isAdvanced
}

func NewCourse(name string, isAdvanced bool) *Course {
	return &Course{
		name:       name,
		isAdvanced: isAdvanced,
	}
}

type Person struct {
	courses map[*Course]bool
}

func (p *Person) GetCourses() map[*Course]bool {
	return p.courses
}

func (p *Person) SetCourses(arg map[*Course]bool) {
	p.courses = arg
}

func main() {
	kent := &Person{}
	mp := make(map[*Course]bool)
	mp[NewCourse("smalltalk programming", false)] = true
	mp[NewCourse("appreciating single malts", true)] = true
	kent.SetCourses(mp)

	refact := NewCourse("refactoring", true)
	kent.GetCourses()[refact] = true
	kent.GetCourses()[NewCourse("brutal sarcasm", false)] = true
	delete(kent.GetCourses(), refact)
}
