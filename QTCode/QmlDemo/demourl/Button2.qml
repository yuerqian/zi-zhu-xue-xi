import QtQuick 2.0

Rectangle {
    id:root
    width: 100
    height: 30
    color: "lightsteelblue"
    border.color: "slategrey"

    signal clicked()

    property alias text:label.text//别名，暴露子元素文本属性

    Text {
        id: label
        text: qsTr("start")
        anchors.centerIn: parent
    }
    MouseArea{
        anchors.fill: parent
        onClicked: {
            root.clicked()
        }
    }

}
