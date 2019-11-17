from socket import *
from datetime import datetime
UDP_port = 12000
UDP_IP = '127.0.0.1'

serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('',UDP_port))
print("server ready")
while True:
	sentence, clientAddress = serverSocket.recvfrom(1024)
	sentence = sentence.decode()
	if (sentence == "What is the current date and time?"):
		dateString = datetime.now().strftime("%m/%d/%Y, %H:%M:%S")
		dateString = "Current Date and Time –" + dateString
		serverSocket.sendto(dateString.encode(),clientAddress)	
	else:
		errorString = "invalid string"
		serverSocket.sendto(errorString.encode(),clientAddress)	
	