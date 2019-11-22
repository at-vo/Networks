#   Dat Vo
#   250983323
import binascii
import socket
from socket import timeout
import struct
import sys
import hashlib
#define Constants
CONST_TIMEOUT = 0.009 # 9ms
UDP_IP = "127.0.0.1"
UDP_PORT = 14000

#Assign Packet data
packet_data = ["NCC-1701","NCC-1422","NCC-1017"]

print("UDP target IP:", UDP_IP)
print("UDP target port:", UDP_PORT)

# initialize reference to ack and seq
ack = 0
seq = 0

for data in packet_data:
    UDP_Packet = createPacket(ack,seq,data)
    #Send the UDP Packet
    sock = socket.socket(socket.AF_INET, # Internet
                        socket.SOCK_DGRAM) # UDP
    sock.sendto(UDP_Packet, (UDP_IP, UDP_PORT))
    sock.settimeout(CONST_TIMEOUT)

    # imitate do while loop
    while True:
        #response from server
        data, serverAddress = sock.recvfrom(1024)
        unpacker = struct.Struct('I I 32s') # (ack, seq, chksum)
        server_reponse = unpacker.unpack(data) 
        print("response received:", server_reponse)
        #assign references
        response_ack = server_reponse[0]
        response_seq = server_reponse[1]
        response_chksum = server_reponse[3]

        if (response_seq != seq) or (sock.gettimeout() == 0.0):
            UDP_Packet = createPacket(ack,seq,data) # create packet
            sock.sendto(UDP_Packet, (UDP_IP, UDP_PORT)) # send packet again
            sock.settimeout(CONST_TIMEOUT) # reset timer
        else:
            break

    seq = changeSeq(seq)

sock.close()

def createPacket(ack,seq,data):
    #Create the Checksum
    bytes_data = bytes(data)
    values = (ack,seq,bytes_data)
    UDP_Data = struct.Struct('I I 8s')
    packed_data = UDP_Data.pack(*values)
    chksum =  bytes(hashlib.md5(packed_data).hexdigest(), encoding="UTF-8")
                                                                                                                                        
    #Build the UDP Packet
    values = (ack,seq,bytes_data,chksum)
    UDP_Packet_Data = struct.Struct('I I 8s 32s')
    UDP_Packet = UDP_Packet_Data.pack(*values)
    return UDP_Packet

def changeSeq(seq):
    if seq == 0 :
        seq = 1
    else:
        seq = 0
    return seq