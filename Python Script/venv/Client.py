import socket
SERVER_IP = "77.137.73.138"
SERVER_PORT = 8200

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connecting to remote computer 80
server_address = (SERVER_IP, SERVER_PORT)
sock.connect(server_address)

msg = "Hello"
sock.sendall(msg.encode())

server_msg = sock.recv(1024)
server_msg = server_msg.decode()
print(server_msg)
