import sys
import telnetlib
import time

HOST = "192.168.87.234"

tn = telnetlib.Telnet(HOST)

user = "admin"
password = "chromasens"

tn.read_until("Login: ")
tn.write(user + "\r\n")

if password:
    tn.read_until("Password: ")
    tn.write(password + "\r\n")

#: Message start token.
STX = b'\x02'
#: Message end token.
ETX = b'\x03'

def cmd(command):
    tn.write(STX + command + ETX + '\r\n')

if __name__ == "__main__":
    #tn.read_some()
    cmd("IY E 1200")
    cmd("LC 1")
    time.sleep(10.0)
    cmd("LC 0")

    #while True:
    #    comm = raw_input("Command: ")
    #    cmd(comm)
