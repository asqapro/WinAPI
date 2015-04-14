import re
from mechanize import Browser
import socket
from random import randint

TCP_IP_OWN = socket.gethostbyname(socket.gethostname())
    
def handshake():
    TCP_PORT_OWN = randint(1,6000)
    print "Tell your trading partner this IP: " + TCP_IP_OWN
    print "Tell your trading partner this port #: " + str(TCP_PORT_OWN)
    BUFFER_SIZE = 20

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    try:
        s.bind((TCP_IP_OWN, TCP_PORT_OWN))
    except:
        s.close()
        handshake_recieve()
    s.listen(1)

    conn, addr = s.accept()
    print "Connection established with " + addr
    while True:
        data = conn.recv(BUFFER_SIZE)
        if not data: continue
        print "Partner data recieved."
        break
    conn.close()
    s.close()

def start():
    print "Recieving data."
    handshake()

start()
