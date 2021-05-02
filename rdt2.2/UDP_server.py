import binascii
import socket
import struct
import sys
import hashlib
import random
import time

UDP_IP = "127.0.0.1"
UDP_PORT = 16001
unpacker = struct.Struct('I I 8s 32s')
respAck = 1 # response ack


def main():
    #Create the socket and listen
    sock = socket.socket(socket.AF_INET, # Internet
                        socket.SOCK_DGRAM) # UDP
    sock.bind((UDP_IP, UDP_PORT))

    curr_sequence = 0 #record current seq expected

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
        # #Network functions
        data = Packet_Checksum_Corrupter(data)
        loss = Network_Loss()
        if loss==1:
            #do not send packet
            pass
        else:
            if seq==curr_sequence:
                #Create the Checksum for comparison
                values = (ack,seq,data)
                packer = struct.Struct('I I 8s')
                packed_data = packer.pack(*values)
                chksum =  bytes(hashlib.md5(packed_data).hexdigest(), encoding="UTF-8")
                #Compare Checksums to test for corrupt data
                if packet_chksum == chksum:
                    print('CheckSums Match, Packet OK')
                    UDP_Packet = createACK(respAck,seq,data)
                    curr_sequence = changeSeq(curr_sequence)
                    Network_Delay()
                    sock.sendto(UDP_Packet,addr)
                    print("ack resp sent:",UDP_Packet)

                else:
                    print('Checksums Do Not Match, Packet Corrupt')
                    temp_sequence = changeSeq(curr_sequence)
                    UDP_Packet = createACK(respAck,temp_sequence,data)
                    Network_Delay()
                    sock.sendto(UDP_Packet,addr)
                    print("nak resp sent:",UDP_Packet)
            else:
                UDP_Packet = createACK(respAck,curr_sequence,data)
                Network_Delay()
                sock.sendto(UDP_Packet,addr)
                print("ack resp resent:",UDP_Packet)

    sock.close()
def createACK(respAck,seq, data): #creates the ACK packet to return
    #Create the Checksum to return
    response_values = (respAck,seq, data)
    response_packer = struct.Struct('I I 8s')
    response_packed_data = response_packer.pack(*response_values)
    chksum =  bytes(hashlib.md5(response_packed_data).hexdigest(), encoding="UTF-8")
    #create packet to return
    packet_values = (respAck,seq,data,chksum)
    UDP_Packet_Data = struct.Struct('I I 8s 32s')
    UDP_Packet = UDP_Packet_Data.pack(*packet_values)
    return UDP_Packet

def changeSeq(seq): #changes the sequence number
    if seq == 0 :
        seq = 1
    else:
        seq = 0
    return seq

### Network Functions ###
def Network_Delay():
    if True and random.choice([0,1,0]) == 1: # Set to False to disable Network Delay. Default is 33% packets are delayed
       time.sleep(.01)
       print("Packet Delayed")
    else:
        print("Packet Sent")

def Network_Loss():
    if True and random.choice([0,1,1,0]) == 1: # Set to False to disable Network Loss. Default is 50% packets are lost
        print("Packet Lost")
        return(1)
    else:
        return(0)

def Packet_Checksum_Corrupter(packetdata):
     if True and random.choice([0,1,0,1]) == 1: #  # Set to False to disable Packet Corruption. Default is 50% packets are corrupt
        print("packet corrupt")
        return(b'Corrupt!')
     else:
        return(packetdata)


main()