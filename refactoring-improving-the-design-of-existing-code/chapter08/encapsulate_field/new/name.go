package new

type Foo struct {
	name string
}

func (f *Foo) GetName() string {
	return f.name
}

func (f *Foo) SetName(arg string) {
	f.name = arg
}
