package main
import (
  "./communicate"
  "net"
  "fmt"
  "time"
)

func main() {
  conn, _ := net.Dial("tcp", "127.0.0.1:8081")
  now := time.Now().UnixNano() / int64(time.Millisecond)
  fmt.Fprintf(conn, "%d %d\n", 1, now)
  for i:=1;;i++ {
    err := communicate.Communicate(conn, i)
    if err!=nil {break}
  }
}