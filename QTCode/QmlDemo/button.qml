import QtQuick 2.6

Rectangle {
    id:root
    width: 100
    height: 30
    color: "lightsteelblue"
    border.color: "slategrey"

    signal clicked()

    property alias text:label.text

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

    focus: true//也要获得焦点，才能够接收事件
    Keys.onPressed: {
        console.log("Loaded item captured: ", event.text);
        event.accepted = true;//不会再向父元素传递事件
    }

}
