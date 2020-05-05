package new

type Rental struct {
	movie *Movie

	daysRented int
}

func NewRental(movie *Movie, daysRented int) *Rental {
	return &Rental{
		movie:      movie,
		daysRented: daysRented,
	}
}

func (r *Rental) GetDaysRented() int {
	return r.daysRented
}

func (r *Rental) GetMovie() *Movie {
	return r.movie
}

func (r *Rental) GetCharge() float64 {
	return r.movie.GetCharge(r.daysRented)
}

func (r *Rental) GetFrequentRenterPoints() int {
	return r.movie.GetFrequentRenterPoints(r.daysRented)
}
