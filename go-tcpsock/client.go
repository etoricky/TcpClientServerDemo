package main
import (
  "net"
  "time"
)


func main() {
  conn, err := net.Dial("tcp", "google.com:80") // or net.DialTimeout("tcp", ":8080", 2 * time.Second)
  if err != nil {
    //handle error
  }

  conn, err := net.DialTimeout("tcp", ":8080", 2 * time.Second)
  if err != nil {
    //handle error
  }
}