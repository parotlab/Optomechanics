from PyQt5.QtCore import QObject, pyqtSignal
import serial, time

arduino = serial.Serial("COM4",9600)

class Logic(QObject):
    signal_receive_data = pyqtSignal(bool)

    def __init__(self):
        super().__init__()

    def move(self,angle, speed):
        if (angle.isdigit() == True) and (speed.isdigit() == True):

            #Se ajusta velocidad
            speed_encrypted = str(20000 + int(speed))
            arduino.write(speed_encrypted.encode())
            time.sleep(1)

            #Hacemos el movimiento
            steps = round(6400/360) * int(angle)     #Convertimos el angulo a steps
            steps_encrypted = str(10000 + steps)    #Encriptamos el mensaje
            arduino.write(steps_encrypted.encode())  #Convertimos a bytes
            time.sleep(2)
            
            self.signal_receive_data.emit(True)

        else:
            self.signal_receive_data.emit(False)



