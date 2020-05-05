package old

type Reading1 struct{}
type Reading2 struct{}

func lastElement() interface{} {
	return &Reading1{}
}

func LastReading() *Reading1 {
	return lastElement().(*Reading1)
}
