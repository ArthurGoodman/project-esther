import Qt

app = new QApplication

msgBox = new QMessageBox
msgBox.setTitle("Message")
msgBox.setText("Hello, World!")
msgBox.show()

app.exec()
