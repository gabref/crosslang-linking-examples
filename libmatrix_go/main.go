package main

import "C"

func stringToCChar(s string) *C.char { return C.CString(s)}
func CCharToString(c *C.char) string { return C.GoString(c) }

//export Add
func Add(a, b int) int {
	return a + b
}

//export Concat
func Concat(a, b *C.char) *C.char {
	c := CCharToString(a)
	d := CCharToString(b)
	return stringToCChar(c + d)

}

//export Multiply
func Multiply(a, b int) int {
	return a * b
}

//export Repeat
func Repeat(s *C.char, n int) *C.char {
	s_go := CCharToString(s)
	result := ""
	for i := 0; i < n; i++ {
		result += s_go

	}
	return stringToCChar(result)
}

func main() {}
