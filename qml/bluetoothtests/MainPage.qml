import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    tools: commonTools

    property bool fakeStarted: false

    Item {

        anchors.centerIn: parent
        height: childrenRect.height
        width: childrenRect.width

        Button{
            id: startButton
            anchors {
                top: parent.top
                horizontalCenter: parent.horizontalCenter
            }
            text: (fakeStarted) ? "STOP": "START"
            onClicked: {
                if (fakeStarted) {
                    hidServer.stop();
                    fakeStarted = false;
                } else {
                    hidServer.start();
                    fakeStarted = true;
                }
            }
        }

        Button{
            id: sendKeyDown
            anchors {
                top: startButton.bottom
                horizontalCenter: parent.horizontalCenter
                topMargin: 10
            }
            text: "key simulation"
            onPressedChanged: {
                if (fakeStarted === false) {
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
    }

}
