try:
        #Create the Checksum
        values = (acknum, seqnum, data.encode())
        UDP_Data = struct.Struct('I I 8s')
        packed_data = UDP_Data.pack(*values)
        chksum =  bytes(hashlib.md5(packed_data).hexdigest(), encoding="UTF-8")

        #Build the UDP Packet
        values = (acknum, seqnum, data.encode() ,chksum)
        UDP_Packet_Data = struct.Struct('I I 8s 32s')
        UDP_Packet = UDP_Packet_Data.pack(*values)


        clientSocket.sendto(UDP_Packet, (UDP_IP, UDP_PORT))
        print("Packet {0} sent." .format(values))
        while True:
            # Hopefully receiving ACK or timeout error
            inData, addr = clientSocket.recvfrom(1024)

            inPacket = unpacker.unpack(inData)

            print("Packet received: {0} from {1}" .format(inPacket, addr))

            if notCorrupt(inPacket):
                print("Packet is not corrupt")

                # ACK received
                if (inPacket[0] == 1 and inPacket[1] == seqnum):
                    return True

                # ACK for a different packet received re enter while loop and wait for right ACK
                elif inPacket[0] == 1:
                    print("Received wrong ACK")

                # Didn't receive an  ACK
                else:
                    print("Didn't receive an ACK")
                    return False

            else:
                print("Received corrupt ACK")

    # Timeout... send again
    except socket.timeout as err:
        print("Timeout waiting for ACK, resend packet")
        return sendPacket(acknum, seqnum, data, clientSocket)


# Function to check checksums for corruption
def notCorrupt(inPacket):
        values = (inPacket[0], inPacket[1], inPacket[2])
        UDP_Data = struct.Struct('I I 8s')
        inPacketchksum = bytes(hashlib.md5(UDP_Data).hexdigest(), encoding="UTF-8")
        return (inPacketchksum == inPacket[3])