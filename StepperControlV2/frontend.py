import sys
from PyQt5 import uic
from PyQt5.QtWidgets import QApplication
from PyQt5.QtCore import pyqtSignal

windows_name, base_class = uic.loadUiType("menu.ui")

class MainWindow(windows_name, base_class):

    signal_button = pyqtSignal(str,str)

    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.button.clicked.connect(self.push_button)
        self.show()
    

    def push_button(self):
        angle = self.angle_label.text()
        speed = self.speed_label.text()
        self.signal_button.emit(angle, speed)

    def text(self,bool):
        if bool == True:
            print("se ha movido")
            self.texto.setText("Se ha movido")
        else:
            print("no se numero valido")
            self.texto.setText("Numero invalido")



if __name__ == '__main__':
    app = QApplication([])
    form = MainWindow()
    form.show()
    sys.exit(app.exec_())