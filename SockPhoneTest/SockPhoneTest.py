import socket, sys, array

def GenHeader(length):
    arr = array.array('c')
    arr.fromstring('0000')
    ss = str(length)
    len_of_ss = len(ss)
    for i in range(-len_of_ss, 0):
        arr[i] = ss[i]
        print 'arr[' + str(i) + '] = ss[' + str(i) + ']'
    head = arr.tostring()
    return head

if __name__ == '__main__':
    ip = "192.168.0.40"
    port = 7810

    in_file = open("test.xml")
    ss = in_file.read()
    head = GenHeader(len(ss))

    print "head: " + head
    print "body: " + ss
    print "length: " + str(len(ss))

    buf = head + ss

    print "ip: ", ip
    print "port: " , port

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((ip, port))

    sock.send(buf)

    print sock.recv(1024)
    print sock.recv(1024)

    sock.close()

