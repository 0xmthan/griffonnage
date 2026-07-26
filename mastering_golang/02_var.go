package main

import "fmt"

func main() {
	var intNum int = 34
	var floatNum float64 = 44.3
	fmt.Println(float64(intNum))
	fmt.Println(floatNum)
	fmt.Println(float64(intNum) + floatNum)

	var intNum1 int = 5
	var intNum2 int = 2
	fmt.Println(intNum1 / intNum2)
	fmt.Println(intNum1 % intNum2)

	var string string = "String" + " " + "ƒƒƒ"
	fmt.Println(string)

	var char rune = 'a'
	fmt.Println(char)

	var boolean bool = false
	fmt.Println(boolean)

	testVar := "test"
	fmt.Println(testVar)

	testVar1 := 43
	fmt.Println(testVar1)

	testVar2 := true
	fmt.Println(testVar2)

	const x, y, z int = 12, 55, 98
	fmt.Println(x, y, z)

}
