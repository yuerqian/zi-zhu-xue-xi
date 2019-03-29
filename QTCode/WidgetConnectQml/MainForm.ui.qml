import QtQuick 2.6
import People.com 1.0

Rectangle {
    property alias mouseArea: mouseArea
    //    property alias textEdit: textEdit
    //qml发出的信号
    signal qmlsignal
    //接收widget信号
    signal widgetsignal
    id: root

    //    onWidgetsignal: {

    //        //        console.log('Qml recveice widget signal!')
    //    }
    width: 360
    height: 360
    color: "#9d6262"
    property alias text1: text1
    property alias textEdit: textEdit

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        Image {
            id: image
            x: 47
            y: 23
            width: 271
            height: 138
            source: "/image/aaa.png"
        }
        //        onClicked: {

        //            //            console.log('signal is send!')
        //            //            qmlsignal() //发送信号
        //        }
    }

    TextEdit {
        id: textEdit
        text: qsTr("Enter some text...")
        font.family: "Arial"
        selectionColor: "#00801c"
        verticalAlignment: Text.AlignVCenter
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        Rectangle {
            anchors.fill: parent
            anchors.margins: -10
            color: "transparent"
            border.width: 1
        }
    }

    Text {
        id: text1
        x: 42
        y: 152
        width: 262
        height: 85
        color: "#000000"
        objectName: "text"
        text: persontwo.idCard.validDate
        fontSizeMode: Text.VerticalFit
        font.pixelSize: 12
        Component.onCompleted: {
            person.name2 = "mynewname"
        }
    }
    Person22 {
        id: persontwo
        idCard: IDCard22 {
            number: "11234567890"
            validDate: "2008.10.01-2018.10.01"
        }
    }
}
