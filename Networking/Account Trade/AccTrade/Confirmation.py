from mechanize import Browser
import subprocess

def login():
    br = Browser()
    br.open("http://www.aeriagames.com/account/login?destination=%2F%2Fava.aeriagames.com%2F")
    for form in br.forms():
        if form.attrs['id'] == 'account_login':
            br.form = form
            break
    # Browser passes through unknown attributes (including methods)
    # to the selected HTMLForm (from ClientForm).
    user = raw_input("Enter your username: ")
    password = raw_input("Enter your password: ")

    br.form["edit[id]"] = user
    br.form["edit[pass]"] = password
    response = br.submit()  # submit current form
    content = response.get_data()
    if content.find("Sorry. Unrecognized username or password.") != -1:
        print "Error: email or password incorrect."
        login()
    if content.find("The confirmation code is not correct.") != -1:
        print "Error: captcha activated."
        login()
    return user + " " + password



def start():
    arg = login()
    subprocess.call(["Handshake-Send.exe", arg])

start()
