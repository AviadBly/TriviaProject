import socket
SERVER_IP = "---"
SERVER_PORT = 00

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connecting to remote computer 80
server_address = (SERVER_IP, SERVER_PORT)
sock.connect(server_address)

msg = "Hello"
sock.sendall(msg.encode())
