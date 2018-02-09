from threading import Thread
import serial, json, time
import serial.tools.list_ports

DESCRIPTION = 'USB-SERIAL CH340'

class ArduinoConnection(Thread):
    def __init__(self, promise):
        super().__init__()
        self.connection = None
        self.port = None
        self.promise = promise
        self.running = True

    def run(self):
        while self.running:
            if not self.is_connected():
                self.listen()
            else:
                self.promise(self.read_data())

    def close(self):
        self.running = False
        self.join()

    def listen(self):
        found = False
        print("Listening for Arduino...")
        while not found:
            ports = list(serial.tools.list_ports.comports())
            for p in ports:
                if DESCRIPTION in p.description:
                    print("Found one at port: "+p.device)
                    self.port = p.device
                    found = True
                    break
        print("Connecting to Arduino...")
        time.sleep(0.5)
        try:
            self.connection = serial.Serial(self.port, 9600)
        except:
            self.connection = None
            self.port = None
        print("Connected!")

    def is_connected(self):
        return self.connection != None

    def read_data(self):
        try:
            json_str = self.connection.readline()[:-2].decode('UTF-8')
            return json.loads(json_str)
        except:
            print("Lost connection to Arduino. Closing Port: " + self.port)
            self.connection.close()
            self.connection = None
            self.port = None
            return {"voltage":0.0, "temp":0.0}
