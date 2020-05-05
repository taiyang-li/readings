package old

import (
	"fmt"

	"github.com/golang-collections/collections/stack"
)

type ResourcePool struct {
	available stack.Stack
	allocated stack.Stack
}

func (p *ResourcePool) GetResource() *Resource {
	defer func() {
		if err := recover(); err != nil {
			fmt.Println("error:", err)
		}
	}()

	result := p.available.Pop().(*Resource)
	p.allocated.Push(result)
	return result
}

type Resource struct {
}
