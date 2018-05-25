package main
import (
  "net"
  "./communicate"
  "time"
  "bufio"
  "fmt"
  "strings"
  "strconv"
)

func printDelay(message string) error {
  fields := strings.Fields(message)
  n, err := strconv.ParseInt(fields[0], 10, 64)
  if err != nil {return err}
  t, err := strconv.ParseInt(fields[1], 10, 64)
  if err != nil {return err}
  now := time.Now().UnixNano() / int64(time.Millisecond)
  delay := now - t
  fmt.Printf("%d %d\n", n, delay)
  return nil
}

func main() {
  ln, _ := net.Listen("tcp", ":8081")
  for {
    conn, _ := ln.Accept()
    record := communicate.Record{time.Now(), 0}
    reader  := bufio.NewReaderSize(conn, 4096*1024*10)
    for i:=1;;i++ {
      reader.ReadString('\n')
      //printDelay(message)
      if time.Now().Sub(record.LastTime).Seconds()>1 {
        fmt.Printf("Rate = %d\n", i-record.Count)
        record.Count = i
        record.LastTime = time.Now()
      }
    }
  }
}