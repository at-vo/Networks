#   Dat Vo
#   250983323
import binascii
import socket
from socket import timeout
import struct
import sys
import hashlib
import random
#define Constants
CONST_TIMEOUT = 0.009 # 9ms
UDP_IP = "127.0.0.1"
UDP_PORT = 16001

def main():
    #Assign Packet data
    packet_data = ["NCC-1701","NCC-1422","NCC-1017"]
    
    print("UDP target IP:", UDP_IP)
    print("UDP target port:", UDP_PORT)

    # initialize reference to ack and seq
    ack = 0
    seq = 0

    for data in packet_data:
        chksum = createChksum(ack,seq,data.encode())
        UDP_Packet = createPacket(ack,seq,data.encode(),chksum)
        #Send the UDP Packet
        sock = socket.socket(socket.AF_INET, # Internet
                            socket.SOCK_DGRAM) # UDP
        sock.sendto(UDP_Packet, (UDP_IP, UDP_PORT))
        print("packet sent:", UDP_Packet)

        # imitate do while loop
        while True:
            try:
                sock.settimeout(CONST_TIMEOUT)
                #response from server
                data, serverAddress = sock.recvfrom(1024)
                unpacker = struct.Struct('I I 8s 32s') # (ack, seq, data, chksum)
                server_reponse = unpacker.unpack(data) 
                print("response received:", server_reponse)
                #assign references
                response_ack = server_reponse[0]
                response_seq = server_reponse[1]
                response_data = server_reponse[2]
                response_chksum = server_reponse[3]
                check = createChksum(response_ack,response_seq,response_data)
                if check == response_chksum:
                    if response_ack!=ack:
                        if (response_seq != seq):
                            sock.sendto(UDP_Packet, (UDP_IP, UDP_PORT)) # send packet again
                            print("packet resent:", UDP_Packet)
                        else:
                            break
                else:
                    sock.sendto(UDP_Packet, (UDP_IP, UDP_PORT)) # send packet again
                    print("checksum corrupt. packet resent:",UDP_Packet)
            except socket.timeout as err:
                print("timeout\n")
                sock.sendto(UDP_Packet, (UDP_IP, UDP_PORT)) # send packet again
                print("packet sent:",UDP_Packet)
                sock.settimeout(CONST_TIMEOUT) # reset timer
                #print("packet resent")

        seq = changeSeq(seq)

    sock.close()

def createPacket(ack,seq,data,chksum):                                                                                                                                
    #Build the UDP Packet
    values = (ack,seq,bytes(data),chksum)
    UDP_Packet_Data = struct.Struct('I I 8s 32s')
    UDP_Packet = UDP_Packet_Data.pack(*values)
    return UDP_Packet

def createChksum(ack,seq,data):
    #Create the Checksum
    bytes_data = bytes(data)
    values = (ack,seq,bytes_data)
    UDP_Data = struct.Struct('I I 8s')
    packed_data = UDP_Data.pack(*values)
    chksum =  bytes(hashlib.md5(packed_data).hexdigest(), encoding="UTF-8")
    return chksum

def changeSeq(seq):
    if seq == 0 :
        seq = 1
    else:
        seq = 0
    return seq
main()