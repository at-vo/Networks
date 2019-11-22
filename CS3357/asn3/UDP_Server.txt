#   Dat Vo
#   250983323
import binascii
import socket
import struct
import sys
import hashlib

UDP_IP = "127.0.0.1"
UDP_PORT = 14000
unpacker = struct.Struct('I I 8s 32s')


#Create the socket and listen
sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

curr_sequence = 0 #record current seq expected
respAck = 1 # response ack

while True: 
    #Receive Data
    data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
    UDP_Packet = unpacker.unpack(data)
    print("received from:", addr)
    print("received message:", UDP_Packet)
    #Assign references to ack, seq, data, chcksum
    ack = UDP_Packet[0]
    seq = UDP_Packet[1]
    data = UDP_Packet[2]
    packet_chksum = UDP_Packet[3]
    #check if duplicate seq
    if curr_sequence == seq:
        #Create the Checksum for comparison
        values = (ack,seq,data)
        packer = struct.Struct('I I 8s')
        packed_data = packer.pack(*values)
        chksum =  bytes(hashlib.md5(packed_data).hexdigest(), encoding="UTF-8")
        #Compare Checksums to test for corrupt data
        if packet_chksum == chksum:
            print('CheckSums Match, Packet OK')
            respAck = 1
            UDP_Packet = createACK(respAck,seq)
            curr_sequence = changeSeq(curr_sequence)
            sock.sendto(UDP_Packet,addr)
        else:
            print('Checksums Do Not Match, Packet Corrupt')
            curr_sequence = changeSeq(curr_sequence)
            UDP_Packet = createACK(respAck,seq)
            sock.sendto(UDP_Packet,addr)
    #not expected sequence
    # else:
    #     curr_sequence = seq
    #     UDP_Packet = createACK(respAck,seq)
    #     sock.sendto(UDP_Packet,addr)


def createACK(respAck,seq):
    #Create the Checksum to return
    response_values = (respAck,seq)
    response_packer = struct.Struct('I I')
    response_packed_data = response_packer.pack(*response_values)
    chksum =  bytes(hashlib.md5(response_packed_data).hexdigest(), encoding="UTF-8")
    #create packet to return
    packet_values = (ack,seq,chksum)
    UDP_Packet_Data = struct.Struct('I I 32s')
    UDP_Packet = UDP_Packet_Data.pack(*packet_values)
    return UDP_Packet

def changeSeq(seq):
    if seq == 0 :
        seq = 1
    else:
        seq = 0
    return seq