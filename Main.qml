import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Arduino Temperatur Monitor")

    Rectangle {
        anchors.fill: parent
        color: "#1e1e2e"

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 30

            // Bağlantı statusu
            Text {
                Layout.alignment: Qt.AlignHCenter
                text: arduinoBackend.connected ? "🟢 Qoşulub" : "🔴 Qoşulmayıb"
                color: arduinoBackend.connected ? "#a6e3a1" : "#f38ba8"
                font.pixelSize: 20
            }

            // Temperatur
            ColumnLayout {
                Layout.alignment: Qt.AlignHCenter
                spacing: 5

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: "Temperatur"
                    color: "#cdd6f4"
                    font.pixelSize: 22
                }

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: arduinoBackend.temperature.toFixed(1) + " °C"
                    color: "#fab387"
                    font.pixelSize: 60
                    font.bold: true
                }
            }

            // Rütubət
            ColumnLayout {
                Layout.alignment: Qt.AlignHCenter
                spacing: 5

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: "Rütubət"
                    color: "#cdd6f4"
                    font.pixelSize: 22
                }

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: arduinoBackend.humidity.toFixed(1) + " %"
                    color: "#89b4fa"
                    font.pixelSize: 60
                    font.bold: true
                }
            }
        }
    }
}
