#!/usr/bin/env python
import socket
import sys
from thread import *


def socketTest():
    try:
       #create a socket object IPv4 over TCP
       s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.error, msg:
       print 'Failed to create socket. Error code: ' +str(msg[0]) +    ', Error message; ' + msg[1]
       sys.exit

    print 'Socket Created'

    #Finding ip for www.google.com

    host = 'www.google.com'
    port = 80

    try:
        remote_ip = socket.gethostbyname( host )
    except socket.gaierror:
        #couldnot resolve
        print 'Hostname could not be resolved. Exiting'
        sys.exit()

    print 'IP Address of ' + host + ' is ' + remote_ip

    #Connect to remote server over port number port
    s.connect((remote_ip,port))

    print 'Socket Connected to ' + host + ' on ip ' + remote_ip

    #sending message to remote_ip
    message = "Get / HTTP/1.1\r\n\r\n"

    try:
        #Send the whole string using sendall
        s.sendall(message)
    except socket.error:
        #Send failed
        print 'Send failed'
        sys.exit()

    print 'Message sent successfully'

    #receive data using recv command
    reply = s.recv(4096)

    print reply

    #Closes socket
    s.close()

#function handle for handling connections. This will be used to create threads
def clientthread(conn):
    #sending message to connected client
    conn.send('Welcome to the server. Type something and hit enter\n') #send only takes strings

    #create and infinite loop so that function doesnt terminate and thread doesnt end
    while True:
        #Receiving from client
        data = conn.recv(1024)
        reply = 'OK...' + data
        if not data:
            break
        conn.sendall(reply)
    #come outside of loop and close connection
    conn.close()


def socketServer():
    HOST = '' #Symbolic name meaning all available interfaces
    PORT = 8888 #Arbitrary non-privileged port

    s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    print 'Socket created'

    try:
       #Attempts to bind socket to port number on host
       s.bind((HOST, PORT))
    except socket.error, msg:
       print 'Bind failed. Error code: ' +str(msg[0]) +    ', Error message; ' + msg[1]
       sys.exit
    print 'Socket bind complete'

    #listen on socket
    s.listen(10)
    print 'Socket now listening'

    #now keep server running
    while 1:
        #wait to accept a connection - blocking call
        conn, addr = s.accept()

        #display client information
        print 'Connected with ' + addr[0] + ':' + str(addr[1])

        #now keep talking with client
        data = conn.recv(1024)
        reply = 'OK...'+data
        if not data:
            break

        conn.sendall(reply)

    conn.close()
    s.close()

def socketServerWithThreads():
    HOST = ''
    PORT = 8888
    
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
       s.bind((HOST, PORT))
    except socket.error, msg:
       print 'Bind failed'
       sys.exit()
    
    s.listen(10)
    print 'Socket now listening'

    while 1:
        #wait to accept a connection - blocking call
        conn, addr = s.accept()
        print 'Connect with ' + addr[0] + ':' + str(addr[1])

        #start new thread takes 1st arg as function name to be run, second is the tuple of arguments to the function.
        start_new_thread(clientthread, (conn,))

    s.close()

if __name__ == '__main__':
   socketServerWithThreads()
