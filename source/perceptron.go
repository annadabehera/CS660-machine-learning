package main

import ( "fmt" )

type perceptron struct {
	n 	int
	inp 	[]float64
	weight 	[]float64
	th	 float64
}
func (p *perceptron) input(data []float64) {
	p.inp=make([]float64, len(data))
	copy( p.inp, data )
	p.n=len(p.inp)
	p.set_threshold(float64(p.n))
}
func (p *perceptron) set_threshold(thres float64) {
	p.th=thres
}
func (p *perceptron) output() int {
	var sum float64=0
	for i:=0;i<p.n;i++ {
		sum+=p.inp[i]
	}
	if sum>=p.th{
		return 1
	} else {
		return 0
	}
}
func (p *perceptron) display() {
	fmt.Printf("perceptron {\n\tinput: ")
	fmt.Print(p.inp);
	fmt.Printf("\n\toutput: %d\n}\n", p.output())
}
func main() {
	/* Perceptron for the AND gate */
	var and perceptron
	and.input([]float64{1,0,1})
	and.display()

	and.input([]float64{1,1,1})
	and.display()
}
