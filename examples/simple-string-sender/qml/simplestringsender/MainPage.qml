import QtQuick 1.1
import com.nokia.meego 1.0
import bluetests 1.0

Page {
    id: page
    tools: commonTools

    property bool serverStopped: hidServer.state == HIDServer.IDLE
    property bool serverConnected: hidServer.state == HIDServer.CONNECTED

    Item {
        anchors.centerIn: parent
        height: childrenRect.height
        width: parent.width

        Button{
            id: startButton
            anchors {
                top: parent.top
                horizontalCenter: parent.horizontalCenter
            }
            text: (serverStopped) ? "Start service": "Stop service"
            onClicked: {
                if (serverStopped) {
                    hidServer.start();
                } else {
                    hidServer.stop();
                }
            }
            Connections {
                target: hidServer
                onError: {
                    statusLabel.text = "Error"
                }
                onStateChanged: {
                    if (serverConnected)
                        statusLabel.text = "Connected"
                    else
                        statusLabel.text = "Disconnected"
                }
            }
        }

        Button{
            id: sendKeyDown
            anchors {
                top: startButton.bottom
                horizontalCenter: parent.horizontalCenter
                topMargin: 30
            }
            text: "key simulation"
            onPressedChanged: {
                if (!serverConnected) {
                    console.log("HIDServer not running!");
                    return;
                }

                if (pressed) {
                    console.log("pressed");
                    hidServer.debugKeyDown();
                } else {
                    console.log("released");
                    hidServer.debugKeyUp();
                }
            }
        }

        TextField {
            id: textToSend
            width: sequentialButton.width
            inputMethodHints: Qt.ImhLowercaseOnly;
            text: "teststring123456"
            anchors {
                top: sendKeyDown.bottom
                horizontalCenter: parent.horizontalCenter
                topMargin: 20
            }

        }


        Button{
            id: sequentialButton

            anchors {
                top: textToSend.bottom
                horizontalCenter: parent.horizontalCenter
                topMargin: 10
            }
            text: "seq keydown/keyup"
            onClicked: {
                if (serverStopped) {
                    console.log("HIDServer not running!");
                    return;
                }
                console.log("Sequential");
                hidStringSender.send(textToSend.text);
            }
            Connections {
                target: hidStringSender
                onSent: {
                    statusLabel.text = "Sent \"" + textToSend.text + "\"";
                }
            }
        }
    }

    Label {
        id: statusLabel
        text: ""
        color: "red"
        opacity: 1.0
        Behavior on opacity { NumberAnimation { duration: 500 } }

        onTextChanged: {
            opacity = 1.0;
            resetStatusTimer.start();
        }

        anchors {
            bottom: parent.bottom
            bottomMargin: 10
            horizontalCenter: parent.horizontalCenter
        }
        Timer {
            id: resetStatusTimer
            interval: 2000
            onTriggered: {
                statusLabel.text = "";
                statusLabel.opacity = 0;
            }
        }
    }
}
