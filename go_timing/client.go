package main
import (
  "./communicate"
  "net"
  "fmt"
  "time"
  "bufio"
  "os"
  "runtime/pprof"
  "log"
)

func main() {

  f, err := os.Create("cpu-profile.prof")
  if err != nil {
    log.Fatal(err)
  }
  pprof.StartCPUProfile(f)

  conn, _ := net.Dial("tcp", "127.0.0.1:8081")
  now := time.Now().UnixNano() / int64(time.Millisecond)
  fmt.Fprintf(conn, "%d %d\n", 1, now)
  record := communicate.Record{time.Now(), 0}
  writer := bufio.NewWriterSize(conn, 4096*1024*10)
  for i:=1;;i++ {
    //writer.WriteString(strconv.FormatInt(int64(i), 10) + " " + strconv.FormatInt(now, 10) + "\n")
    n, err := writer.WriteString(" \n")
    if n!=2 || err!=nil {
      fmt.Println(string(n))
      fmt.Println(err)
    }

    if time.Now().Sub(record.LastTime).Seconds()>1 {
      fmt.Printf("Rate = %d\n", i-record.Count)
      record.Count = i
      record.LastTime = time.Now()
    }

    if i>10000000*50 {
      pprof.StopCPUProfile()
      break
    }
  }
}


