import socket
import json
SERVER_IP = "127.0.0.1"
SERVER_PORT = 8200

SIGN_UP_CODE = 100
LOGIN_CODE = 101
# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connecting to remote computer 80
server_address = (SERVER_IP, SERVER_PORT)
sock.connect(server_address)


login_dict = {"username":"user1","password":"1234"}
signup_dict = {"username": "user1", "password": "1234", "mail":"user1@gmail.com"}


signup_msg = bytes(SIGN_UP_CODE) + bytes(len(signup_dict)) + str(signup_dict).encode()
login_msg = bytes(LOGIN_CODE) + bytes(len(login_dict)) + str(login_dict).encode()


data = json.dumps(signup_msg)          #USE EITHER LOGIN_MSG OR SIGNUP MSG
sock.sendall(data.encode())

server_msg = sock.recv(1024)
server_msg = server_msg.decode()
print(server_msg)