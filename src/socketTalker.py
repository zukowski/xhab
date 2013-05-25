#!/usr/bin/env python
import socket
import sys
import select
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

#Function to broadcast chat messages to all connected clients
def broadcast_data (sock, message):
    #Do not send the message to master socket and the client who has send us the message
    for socket in CONNECTION_LIST:
        if socket != server_socket and socket != sock :
            try :
                socket.send(message)
            except :
                # broken socket connection may be, chat client pressed ctrl+c for example
                socket.close()
                CONNECTION_LIST.remove(socket)


if __name__ == '__main__':
    # List to keep track of socket descriptors
    CONNECTION_LIST = []
    RECV_BUFFER = 4096 # Advisable to keep it as an exponent of 2
    PORT = 8888
     
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # this has no effect, why ?
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind(("0.0.0.0", PORT))
    server_socket.listen(10)
 
    # Add server socket to the list of readable connections
    CONNECTION_LIST.append(server_socket)
 
    print "Chat server started on port " + str(PORT)
 
    while 1:
        # Get the list sockets which are ready to be read through select
        read_sockets,write_sockets,error_sockets = select.select(CONNECTION_LIST,[],[])
 
        for sock in read_sockets:
            #New connection
            if sock == server_socket:
                # Handle the case in which there is a new connection recieved through server_socket
                sockfd, addr = server_socket.accept()
                CONNECTION_LIST.append(sockfd)
                print "Client (%s, %s) connected" % addr
                 
                broadcast_data(sockfd, "[%s:%s] entered room\n" % addr)
             
            #Some incoming message from a client
            else:
                # Data recieved from client, process it
                try:
                    #In Windows, sometimes when a TCP program closes abruptly,
                    # a "Connection reset by peer" exception will be thrown
                    data = sock.recv(RECV_BUFFER)
                    if data:
                        broadcast_data(sock, "\r" + '<' + str(sock.getpeername()) + '> ' + data)               
                 
                except:
                    broadcast_data(sock, "Client (%s, %s) is offline" % addr)
                    print "Client (%s, %s) is offline" % addr
                    sock.close()
                    CONNECTION_LIST.remove(sock)
                    continue
     
    server_socket.close()
