import socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('172.16.18.128', 9999)) 
client.send('GET /index.html HTTP/1.1\r\nHost: abc.com\r\n\r\n')
