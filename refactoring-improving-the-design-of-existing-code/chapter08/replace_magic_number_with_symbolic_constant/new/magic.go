package new

const (
	GRAVITATIONAL = 9.81
)

func PotentialEnergy(mass, height float64) float64 {
	return mass * GRAVITATIONAL * height
}
