from PyQt5.QtWidgets import QApplication
from frontend import MainWindow
from backend import Logic
import sys

if __name__ == '__main__':
    def hook(type, value, traceback):
        print(type)
        print(traceback)
    sys.__excepthook__ = hook
    app = QApplication([])

    main_window = MainWindow()
    logic = Logic()

    #signals
    main_window.signal_clock.connect(logic.moveclock)
    main_window.signal_cclock.connect(logic.movecclock)
    logic.signal_receive_data.connect(main_window.text)

    app.exec()
