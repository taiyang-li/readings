package old

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
