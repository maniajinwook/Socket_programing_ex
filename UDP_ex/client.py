#!/usr/bin/env python
 
from socket import *
 
HOST = 'localhost'
PORT = 21566
BUFSIZ = 1024
ADDR = (HOST, PORT)
 
udpCliSock = socket(AF_INET, SOCK_DGRAM)
 
while True:
    data = raw_input()
    if not data:
        break
    udpCliSock.sendto(data,  ADDR)
    #if not data:
    #    break
    #print data
 
udpCliSock.close()
