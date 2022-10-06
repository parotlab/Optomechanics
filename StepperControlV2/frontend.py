import sys
from PyQt5 import uic
from PyQt5.QtWidgets import QApplication
from PyQt5.QtCore import pyqtSignal

windows_name, base_class = uic.loadUiType("menu.ui")

class MainWindow(windows_name, base_class):

    signal_clock = pyqtSignal(str,str)
    signal_cclock = pyqtSignal(str,str)

    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.bclock.clicked.connect(self.clockwise)
        self.bcclock.clicked.connect(self.cclockwise)
        self.show()
    
    def clockwise(self):
        steps = self.angle_label.text()
        speed = self.speed_label.text()
        self.signal_clock.emit(steps, speed)

    def cclockwise(self):
        steps = self.angle_label.text()
        speed = self.speed_label.text()
        self.signal_cclock.emit(steps, speed)

    def text(self,bool):
        if bool == True:
            print("se ha movido")
            self.texto.setText("Se ha movido")
        else:
            print("no es numero valido")
            self.texto.setText("Numero invalido")



if __name__ == '__main__':
    app = QApplication([])
    form = MainWindow()
    form.show()
    sys.exit(app.exec_())