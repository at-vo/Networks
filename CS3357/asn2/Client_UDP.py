import socket
serverIP = '127.0.0.1'
serverPort = 12000

print ("Attempting to contact server at ",serverIP,":",serverPort)
clientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
message = input("send something to the server:")
clientSocket.sendto(message.encode(),(serverIP,serverPort))
modifiedMessage, serverAddress = clientSocket.recvfrom(1024)
print(modifiedMessage.decode())
clientSocket.close()