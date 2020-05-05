package new

type Reading1 struct{}
type Reading2 struct{}

func lastElement() interface{} {
	return &Reading1{}
}

func LastReading() interface{} {
	return lastElement()
}