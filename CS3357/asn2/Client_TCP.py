import socket
serverPort = 12000
TCP_IP = '127.0.0.1'


print ("Attempting to contact server at ",TCP_IP,":",serverPort)
clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientSocket.connect((TCP_IP,serverPort))
sentence = input("send something to the server:")
clientSocket.send(sentence.encode())
msg = clientSocket.recv(1024)
print('From Server: ',msg.decode())
clientSocket.close()
