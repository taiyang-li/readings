package old

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

// MyStack继承Vector的所有方法
type MyStack struct {
	Vector
}
