import sys
import os
import socket
import thread
import datetime

from decimal import *

def request_handler(client, addr):
    print "\n\nRequest from : " + str(addr)
    docRoot = './views/'
    response = ''
    try:
        # Receive HTTP Message
        msg = client.recv(4096)
        if msg:
            print str(addr) + " : \n" + msg
            
            # HTTP Protocol : Only HTTP GET Here
            line = msg.split()
            if line[0] == 'GET':
                if line[1] == '/':
                    doc = 'hello.html'  # Default Page
                else:
                    doc = line[1][1:]   # Requested Page

                doc = docRoot + doc
                fd = open(doc, 'r')
                data = fd.read()

                # HTTP 200 OK
                response = 'HTTP/1.1 200 OK\r\n'
                dt = 'Date: ' + datetime.datetime.now().ctime() + '\r\n'
                sv = 'Server: cchen simpleHTTP server\r\n'
                lm = 'Last-Modified: Thu, 30 Apr 2015 18:02:04 GMT\r\n'
                etag = '176-5116ba5ca5b0c\r\n'
                ar = 'Accept-Ranges: bytes\r\n'
                length = 'Content-Length: ' + str(os.path.getsize(doc)) + '\r\n'
                ka = 'Keep-Alive: timeout=5, max=99\r\n'
                cn = 'Connection: Keep-Alive\r\n'
                tp = 'Content-Type: text/html; charset=UTF-8\r\n'
                
                response = response + dt + sv + lm + etag + ar + length + ka + cn + tp + '\r\n'
                client.send(response)

                # Transmit the requested file
                for d in range(0, len(data)):
                    client.send(data[d])

        client.close()

    except IOError:
        # Requested page not found.
        print 'not found!'

        page404 = docRoot + '404.html'

        fd = open(page404, 'r')
        data = fd.read()        

        # HTTP 404 Not Found
        response = 'HTTP/1.1 404 Not Found\r\n'
        dt = 'Date: ' + datetime.datetime.now().ctime() + '\r\n'
        sv = 'Server: cchen simpleHTTP server\r\n'
        length = 'Content-Length: ' + str(os.path.getsize(page404)) + '\r\n'
        cn = 'Connection: close\r\n'
        tp = 'Content-Type: text/html; charset=iso-8859-1\r\n'

        response = response + dt + sv + length + cn + tp + '\r\n'
        client.send(response)        

        # 404 Page
        for d in range(0, len(data)):
            client.send(data[d])

        client.close()    
    
def start(port):
    #domainName = socket.getfqdn()
    domainName = 'localhost'
    pt = 3456
    if port :
        pt = int(Decimal(port))

    print "start my server at: " + domainName + ":" + str(pt)

    # create a socket for server
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # assign the address and port number
    server.bind((domainName, pt))
    # listen for connections, max 5 connections in queue
    server.listen(5)

    while(1):
        # Waiting for New Connection
        (client, addr) = server.accept()
        if client:
            #Start a thread to process HTTP requests from this client
            thread.start_new_thread(request_handler, (client, addr))                


start(sys.argv[1])
