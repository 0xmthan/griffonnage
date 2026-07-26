package main

import "fmt"

func main() {
	str := "print this"
	print_func(str)
	fmt.Println(return_some(1))
	fmt.Println(go_up(0, 0, 0))
}

func print_func(str string) {
	fmt.Println(str)
}

func return_some(number int) int {
	return 55 + number
}

func go_up(x int, y int, z int) (int, int, int) {
	return x, y + 2, z
}
