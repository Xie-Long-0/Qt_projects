import QtQuick.Window 2.15
import QtQuick 2.15

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "BasicComponents"

    Screen01 {
        id: mainScreen

        anchors.centerIn: parent
    }

}

