import socket
from datetime import datetime
TCP_IP = '127.0.0.1'
TCP_PORT = 12000

serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverSocket.bind((TCP_IP, TCP_PORT))
serverSocket.listen(1)
print("server ready")
while True:
	connectionSocket, addr = serverSocket.accept()
	sentence, clientAddress = connectionSocket.recvfrom(1024)
	sentence = sentence.decode()
	if (sentence == "What is the current date and time?"):
		dateString = datetime.now().strftime("%m/%d/%Y, %H:%M:%S")
		dateString = "Current Date and Time –" + dateString
		connectionSocket.send(dateString.encode())	
	else:
		errorString = "invalid string"
		connectionSocket.send(errorString.encode())	
	connectionSocket.close()
