package communicate
import (
  "net"
  "bufio"
  "time"
)

type Record struct {
  LastTime time.Time
  Count int
}

func (r *Record) Communicate(conn net.Conn, i int, rw *bufio.ReadWriter) error {
  return nil
}
