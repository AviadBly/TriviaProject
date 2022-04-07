import socket
SERVER_IP = "77.137.73.138"
SERVER_PORT = 8200

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connecting to remote computer 80
server_address = (SERVER_IP, SERVER_PORT)
sock.connect(server_address)


login_msg = {"username":"user1","password":"1234"}
signup_msg={"username": "user1", "password": "1234", "mail":"user1@gmail.com"}
data=json.dumps(signup_msg)          #USE EITHER LOGIN_MSG OR SIGNUP MSG
sock.sendall(data.encode())

server_msg = sock.recv(1024)
server_msg = server_msg.decode()
print(server_msg)
