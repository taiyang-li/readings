package new

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

func (p *Person) InitializeCourses(arg map[*Course]bool) {
	p.courses = make(map[*Course]bool)
	for c := range arg {
		p.AddCourse(c)
	}
}

func (p *Person) AddCourse(arg *Course) {
	p.courses[arg] = true
}

func (p *Person) RemoveCourse(arg *Course) {
	delete(p.courses, arg)
}

func (p *Person) SetCourses(arg map[*Course]bool) {
	p.courses = arg
}

func main() {
	kent := &Person{}
	mp := make(map[*Course]bool)
	mp[NewCourse("smalltalk programming", false)] = true
	mp[NewCourse("appreciating single malts", true)] = true
	kent.InitializeCourses(mp)

	refact := NewCourse("refactoring", true)
	kent.AddCourse(refact)
	kent.AddCourse(NewCourse("brutal sarcasm", false))
	kent.RemoveCourse(refact)
}
