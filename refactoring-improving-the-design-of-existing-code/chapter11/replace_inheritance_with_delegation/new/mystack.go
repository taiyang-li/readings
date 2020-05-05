package new

type Vector struct {
	data []interface{}
}

func (v *Vector) Push(arg interface{}) {
	v.data = append(v.data, arg)
}

func (v *Vector) Pop() interface{} {
	if len(v.data) == 0 {
		panic("empty container")
	}
	result := v.data[-1]
	v.data = v.data[0:-1]
	return result
}

func (v *Vector) At(index int) interface{} {
	if index < 0 || index >= len(v.data) {
		panic("invalid index")
	}
	return v.data[index]
}

// MyStack包含vector
type MyStack struct {
	vector Vector
}

func (s *MyStack) Push(arg interface{}) {
	return s.vector.Push(arg)
}

func (s *MyStack) Pop() interface{ 
	return s.vector.Pop()
}
