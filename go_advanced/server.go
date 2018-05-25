package main
import (
  "net"
  "./communicate"
)

func main() {
  ln, _ := net.Listen("tcp", ":8081")
  for {
    conn, _ := ln.Accept()
    for i:=1;;i++ {
      err := communicate.Communicate(conn, i)
      if err!=nil {break}
    }
  }
}