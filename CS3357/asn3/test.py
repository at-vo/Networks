try:
    #Create the Checksum
    values = (acknum, seqnum, data.encode())
    UDP_Data = struct.Struct('I I 8s')
    packed_data = UDP_Data.pack(*values)
    chksum = bytes(hashlib.md5(packed_data).hexdigest().encode())

    #Build the UDP Packet
    values = (acknum, seqnum, data.encode() ,chksum)
    UDP_Packet_Data = struct.Struct('I I 8s 32s')
    UDP_Packet = UDP_Packet_Data.pack(*values)


    clientSocket.sendto(UDP_Packet, (UDP_IP, UDP_PORT))

    while True:
        # Hopefully receiving ACK or timeout error
        data, addr = clientSocket.recvfrom(1024)

        inPacket = unpacker.unpack(data)

        print("Packet received: %s from %s", inPacket, addr)

        if notCorrupt(inPacket):
            print("Packet is not corrupt")

            # ACK received
            if (inPacket[0] == "1" and inPacket[1] == seqnum):
                return True

            # ACK for a different packet received re enter while loop and wait for right ACK
            elif inPacket[0] == "1":
                print("Received wrong ACK")
                continue

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