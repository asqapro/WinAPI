import re
from mechanize import Browser
import socket

def login():
    br = Browser()
    br.open("http://www.aeriagames.com/account/login?destination=%2F%2Fava.aeriagames.com%2F")
    for form in br.forms():
        if form.attrs['id'] == 'account_login':
            br.form = form
            break
    # Browser passes through unknown attributes (including methods)
    # to the selected HTMLForm (from ClientForm).
    br.form["edit[id]"] = raw_input("Enter your username: ")
    br.form["edit[pass]"] = raw_input("Enter your password: ")
    response = br.submit()  # submit current form
    content = response.get_data()
    if content.find("Sorry. Unrecognized username or password.") != -1:
        print "Error: email or password incorrect."
        login()
    if content.find("The confirmation code is not correct.") != -1:
        print "Error: captcha activated."
        login()


def handshake():
    TCP_IP_PART = raw_input("Your partner's IP: ")
    TCP_PORT_PART = int(raw_input("Your partner's port #: "))
    BUFFER_SIZE = 20
    MESSAGE = "shake"

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((TCP_IP_PART, TCP_PORT_PART))
    s.send(MESSAGE)
    print "Message sent: " + MESSAGE
    s.close()

def start():
    login()
    print "Transmitting  data."
    handshake()

start()
