import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Rectangle {
    width: 800
    height: 600

    color: "#EEEEEE"

    RowLayout {
        id: rowLayout
        width: 300
        height: 40
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 20

        Text {
            id: text1
            text: qsTr("Text")
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            Layout.preferredWidth: 60
            Layout.fillHeight: true
            Layout.fillWidth: true
            font.pointSize: 12
            padding: 4

            Rectangle {
                anchors.fill: parent
                z: -1
                color: "#AAAAAA"
                radius: 4
                border.color: "#555555"
                border.width: 1
            }
        }

        TextInput {
            id: textInput
            text: qsTr("Text Input")
            verticalAlignment: Text.AlignVCenter
            clip: true
            padding: 4
            Layout.minimumWidth: 150
            Layout.preferredWidth: 200
            Layout.fillWidth: true
            Layout.fillHeight: true
            font.pointSize: 12

            Rectangle {
                anchors.fill: parent
                z: -1
                color: "#FFFFFF"
                radius: 4
                border.color: "#555555"
                border.width: 1
            }
        }
    }

    GridLayout {
        id: gridLayout

        width: 300
        height: 100
        anchors.top: rowLayout.bottom
        anchors.topMargin: 40
        rows: 2
        columns: 2
        anchors.horizontalCenter: parent.horizontalCenter

        Label {
            id: label
            color: "#2200ff"
            text: qsTr("Label")
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 12
            Layout.preferredHeight: 30
            Layout.preferredWidth: 60
            Layout.fillWidth: true
        }

        TextField {
            id: textField
            placeholderText: textField.activeFocus ? qsTr("Inputing...") : qsTr(
                                                         "Text Field")
            Layout.preferredHeight: 36
            Layout.preferredWidth: 160
            Layout.fillWidth: true
            font.pointSize: 12
            verticalAlignment: Text.AlignVCenter
        }

        Label {
            id: label2
            text: qsTr("Label")
            background: Rectangle {
                color: "#00000000"
                radius: 4
                border.color: "#555555"
                border.width: 1
            }

            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            padding: 4
            Layout.preferredHeight: 30
            Layout.preferredWidth: 60
            Layout.fillWidth: true
            font.pointSize: 12
        }

        TextField {
            id: textField2
            echoMode: TextInput.Password
            placeholderText: qsTr("Text Field")
            Layout.preferredHeight: 36
            Layout.fillWidth: true
            font.pointSize: 12
            verticalAlignment: Text.AlignVCenter

            // 根据焦点状态动态改变边框颜色
            background: Rectangle {
                radius: 4
                border.width: textField2.activeFocus ? 2 : 1
                border.color: textField2.activeFocus ? "#2196F3" : "#BDBDBD"
                color: textField2.activeFocus ? "#E3F2FD" : "white"

                Behavior on border.color {
                    ColorAnimation {
                        duration: 150
                    }
                }
                Behavior on color {
                    ColorAnimation {
                        duration: 150
                    }
                }
            }
        }
    }

    Flow {
        id: flow1
        width: 400
        height: 200
        anchors.top: gridLayout.bottom
        anchors.topMargin: 30
        spacing: 30
        anchors.horizontalCenter: parent.horizontalCenter

        Button {
            id: button
            text: qsTr("Button")

            Connections {
                target: button
                function onClicked() {
                    textInput.clear()
                }
            }
        }

        CheckBox {
            id: checkBox
            text: qsTr("Check Box")
            checkState: Qt.Checked

            Connections {
                target: checkBox
                function onToggled() {
                    textInput.visible = checkBox.checked
                }
            }
        }

        ComboBox {
            id: comboBox

            editable: true
            model: ListModel {
                id: model
                ListElement {
                    text: "Banana"
                }
                ListElement {
                    text: "Apple"
                }
                ListElement {
                    text: "Coconut"
                }
            }

            Connections {
                target: comboBox
                function onAccepted() {
                    if (comboBox.find(comboBox.editText) === -1)
                        model.append({
                                         "text": comboBox.editText
                                     })
                }
            }
        }

        RadioButton {
            id: radioButton
            text: qsTr("Radio Button")
            checked: true

            Connections {
                target: radioButton
                function onToggled() {
                    switch1.checked = !radioButton.checked
                }
            }
        }

        RoundButton {
            id: roundButton
            text: "R"

            Connections {
                target: roundButton
                function onClicked() {
                    // 获取当前字符的码点，计算下一个字母（循环 A-Z）
                    // 使用 charCodeAt() 获取字符的 Unicode 码点，再用 String.fromCharCode() 将结果转回字符
                    var code = roundButton.text.charCodeAt(
                                0) - 'A'.charCodeAt(0)
                    var nextCode = (code + 1) % 26
                    roundButton.text = String.fromCharCode(
                                nextCode + 'A'.charCodeAt(0))
                }
            }
        }

        Switch {
            id: switch1
            text: qsTr("Switch")

            Connections {
                target: switch1
                function onToggled() {
                    radioButton.checked = !switch1.checked
                    radioButton1.checked = switch1.checked
                }
            }
        }

        RadioButton {
            id: radioButton1
            text: qsTr("Radio Button")

            Connections {
                target: radioButton1
                function onToggled() {
                    switch1.checked = radioButton1.checked
                }
            }
        }
    }
}
