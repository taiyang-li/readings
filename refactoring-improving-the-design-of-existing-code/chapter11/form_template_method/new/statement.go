package new

import (
	"strconv"
	"strings"
)

type IStatement interface {
	HeaderString(c *Customer) string
	EachRentalString(r *Rental) string
	FooterString(c *Customer) string
}

// 注意，该类并不实现IStatement
type StatementTemplate struct {
	concrete IStatement
}

func NewStatementTemplate() *StatementTemplate {
	t := &StatementTemplate{}
	t.SetType()
	return t
}

func (t *StatementTemplate) SetType(typ string) {
	switch typ {
	case "text":
		t.concrete = &TextStatement{}
	case "html":
		t.concrete = &HtmlStatement{}
	default:
		t.concrete = &TextStatement{}
	}
}

func (t *StatementTemplate) Value() string {
	var builder strings.Builder
	builder.WriteString(concrete.HeaderString())
	for _, each := range c.GetRentals() {
		builder.WriteString(concrete.EachRentalString())
	}
	builder.WriteString(concrete.FooterString())
	return builder.String()

}

type TextStatement struct{}

func (s *TextStatement) HeaderString(c *Customer) string {
	return "Rental Record for " + c.GetName() + "\n"
}

func (s *TextStatement) EachRentalString(r *Rental) string {
	return "\t" + r.GetMovie().GetTitle() + "\t" + strconv.FormatFloat(r.GetCharge(), 'f', -1, 64) + "\n"
}

func (s *TextStatement) FooterString(c *Customer) string {
	result := "Amount owed is " + strconv.FormatFloat(c.GetTotalCharge(), 'f', -1, 64) + "\n"
	result += "You earned " + strconv.Itoa(c.GetTotalFrequencyRenterPoints()) + " frequent renter points"
	return result
}

type HtmlStatement struct{}

func (s *HtmlStatement) HeaderString(c *Customer) string {
	return "<H1>Rentals for <EM>" + c.GetName() + "</EM></H1><P>\n"
}

func (s *HtmlStatement) EachRentalString(r *Rental) string {
	return r.GetMovie().GetTitle() + ":" + strconv.FormatFloat(r.GetCharge(), 'f', -1, 64) + "<BR>\n"
}

func (s *HtmlStatement) FooterString(c *Customer) string {
	result := "<P>You owe <EM>" + strconv.FormatFloat(c.GetTotalCharge(), 'f', -1, 64) + "</EM><P>\n"
	result += "On this rental you earned <EM>" + strconv.Itoa(c.GetTotalFrequencyRenterPoints()) + "</EM> frequent renter points<P>"
	return result
}
