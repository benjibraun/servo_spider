import serial, time, datetime, serial.tools.list_ports
import tkinter as tk
import sys

class ServoControl:
    """GUI for Servo Spider Control"""
    speeds = {9600, 115200}
    def __init__(self, root):
        root.title('servo spider')
        self.port_select = tk.StringVar(root)
        self.speed_slect = tk.StringVar(root)
        self.port_select.set("válassz")
        self.speed_slect.set("válassz")
        tk.Label(root,text="leg =").grid(row=1, column=2)
        tk.Label(root, text="servo = ").grid(row=2, column=2)
        tk.Label(root, text="angle = ").grid(row=3, column=2)
        tk.Label(root, text="serial = ").grid(row=4, column=2)
        self.leg_e = tk.Entry(root)
        self.servo_e = tk.Entry(root)
        self.angle_e = tk.Entry(root)
        self.manula_e = tk.Entry(root)
        self.leg_e.grid(row=1, column=3)
        self.servo_e.grid(row=2, column=3)
        self.angle_e.grid(row=3, column=3)
        self.manula_e.grid(row=4, column=3)
        self.leg_e.insert(0,"0")
        self.servo_e.insert(0, "0")
        self.angle_e.insert(0, "0")
        self.manula_e.insert(0, "0")
        tk.Button(root, text="connect", width=10, command=lambda: my_connection.init_connection(self.port_select.get(), int(self.speed_slect.get()))).grid(row=1, column=4)
        tk.Button(root, text="disconnect", width=10, command=lambda: my_connection.list_ports()).grid(row=2, column=4)
        tk.Button(root, text="move leg", width=10, command=lambda: my_control.execute()).grid(row=3, column=4)
        tk.Button(root, text="send", width=10, command=lambda: my_connection.send()).grid(row=4, column=4)
        tk.Button(root, text="get pos", width=10, command=lambda: my_control.Get_pos(self.leg_e.get(), self.servo_e.get())).grid(row=5,column=4)
        tk.OptionMenu(root, self.port_select, *my_connection.list_ports()).grid(row=1, column=1)
        tk.OptionMenu(root, self.speed_slect, *self.speeds).grid(row=2, column=1)
        self.leg_e.focus_set()

class Control:

    def execute(self):
        leg = int("{0:#b}".format(int(my_gui.leg_e.get())), 2)
        servo = int("{0:#b}".format(int(my_gui.servo_e.get())), 2) << 2
        angle = int("{0:#b}".format(round(int(my_gui.angle_e.get())/10)), 2) << 4
        command = bytearray(1)
        command[0] = leg | servo | angle
        my_connection.send_bytes(command)

    def move_leg(self,leg, servo, angle):
        print(leg)
        print(servo)
        print(angle)
        my_connection.connection.flushInput()
        my_connection.send(leg)
        if my_connection.ack():
            my_connection.connection.flushInput()
            my_connection.send(servo)
        if my_connection.ack():
            my_connection.connection.flushInput()
            my_connection.send(angle)

    def Get_pos(self,leg, servo):

        my_connection.send("999")
        if my_connection.ack():
            my_connection.connection.flushInput()
            my_connection.send(leg)
        if my_connection.ack():
            my_connection.connection.flushInput()
            my_connection.send(servo)
        my_connection.read()

class Connection:

    connection = 0
    send_failed = 0

    def list_ports(self):
        try:
            ports = list(serial.tools.list_ports.comports())
            if len(ports) == 0:
                return ["can't find port"]
            for p in ports:
                print(p)
            return ports
        except:
            print("can't find port")

    def ack(self, message):
        ack = self.read(1)
        print(ack)
        if ack == message:
            print("ack")
            return True
        else:
            return False

    def init_connection(self, device, speed):
        try:
            ports = self.list_ports()
            for p in ports:
                print(p[1])
                if str(p) == device:
                    print("jep")
                    port = p[0]
                    break
            print("port")
            print(int(speed))
            self.connection = serial.Serial(port, int(speed))
            return self.connection
        except:
            print("Unexpected error: connection")

    def disconnect(self):
        pass

    def send_bytes(self, bytes_to_send):
        self.connection.flushInput()
        self.connection.write(bytes_to_send)
        if self.ack(bytes_to_send):
            self.send_failed = 0
            return True
        else:
            print("sending failed")
            self.send_failed += 1
            if self.send_failed > 10:
                return False
            elif not self.send_bytes(bytes_to_send):
                return False
            else:
                return True

    def send_line(self, message):
        try:
            command = bytes(message, 'ASCII')
            self.connection.write(command)
        except:
                print("not send")

    def read(self,num_of_bytes_to_read):
        return self.connection.read(num_of_bytes_to_read)

    def read_line(self):
        try:
            line = self.connection.readline()
            print(str(line))
            line = line.decode('ASCII')
            return line
        except:
            print("read error")


my_connection = Connection()
my_control = Control()
root = tk.Tk()
my_gui = ServoControl(root)
root.mainloop()


