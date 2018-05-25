package communicate
import (
  "net"
  "fmt"
  "bufio"
  "strconv"
  "strings"
  "time"
)

func Communicate(conn net.Conn, i int) error {
  message, err := bufio.NewReader(conn).ReadString('\n')
  if err != nil {return err}
  fields := strings.Fields(message)
  n, err := strconv.ParseInt(fields[0], 10, 64)
  if err != nil {return err}
  t, err := strconv.ParseInt(fields[1], 10, 64)
  if err != nil {return err}
  now := time.Now().UnixNano() / int64(time.Millisecond)
  delay := now - t
  fmt.Printf("%d %d\n", n, delay)
  fmt.Fprintf(conn, "%d %d\n", i, now)
  return nil
}
