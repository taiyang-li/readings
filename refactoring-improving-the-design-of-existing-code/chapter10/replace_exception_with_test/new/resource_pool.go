package new

import (
	"github.com/golang-collections/collections/stack"
)

type ResourcePool struct {
	available stack.Stack
	allocated stack.Stack
}

func (p *ResourcePool) GetResource() *Resource {
	if p.available.Len() == 0 {
		return nil
	}
	result := p.available.Pop().(*Resource)
	p.allocated.Push(result)
	return result
}

type Resource struct{}
