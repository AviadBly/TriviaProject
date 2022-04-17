import socket
import json
SERVER_IP = "127.0.0.1"
SERVER_PORT = 8200

SIGN_UP_CODE = 10
LOGIN_CODE = 20
# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connecting to remote computer 80
server_address = (SERVER_IP, SERVER_PORT)
sock.connect(server_address)


login_dict = {"username":"user1","password":"1234"}
signup_dict = {"username": "user1", "password": "1234", "mail":"user1@gmail.com"}


signup_msg = chr(SIGN_UP_CODE).encode() + len(str(signup_dict)).to_bytes(4, byteorder='big') + str(signup_dict).encode()
login_msg = chr(LOGIN_CODE).encode() + len(str(login_dict)).to_bytes(4, byteorder='big') + str(login_dict).encode()

print(signup_msg, "length: " + str(len(signup_msg)))

# data = json.dumps(signup_msg)          #USE EITHER LOGIN_MSG OR SIGNUP MSG

server_msg = sock.recv(1024)
server_msg = server_msg.decode()

sock.sendall(signup_msg)

print(server_msg)
