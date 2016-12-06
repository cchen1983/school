import sys
import os
import socket
import thread
import datetime

from decimal import *

def http_request(host, port, fname):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        client.connect((host, int(port)))
        req = 'GET /' + fname + ' HTTP/1.1\r\n'

        # Send HTTP GET Request to server
        req = req + '\r\n'
        client.send(req)
        
        #Receive HTTP Response Header
        resp_hdr = client.recv(4096)
        
        #Recevie Requested files
        resp_data = ''
        while(1):
            d = client.recv(1)
            if d:
                resp_data = resp_data + d
            else:
                break
            
        print '### Response from server:'
        print resp_hdr
        print resp_data 

    except socket.error as msg:
        print msg

    client.close()
    sys.exit(0)

http_request(sys.argv[1], sys.argv[2], sys.argv[3])
