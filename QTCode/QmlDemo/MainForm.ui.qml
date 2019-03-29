import QtQuick 2.0

Rectangle {
    id: root
    property alias mouseArea: mouseArea
    property alias textEdit: textEdit
    property alias textEdit2: textEdit2

    width: 360
    height: 360
    color: "#794646"

    //    //    focus: true  //如果父元素获得焦点，子元素也就是loader将不会再接收事件
    //    Keys.onPressed: {
    //        console.log("Captured: ", event.text)
    //        //        event.accepted = true
    //    }
    //    Loader {
    //        id: buttonselect
    //        x: 200
    //        y: 300
    //        focus: true
    //        source: "button.qml"
    //        onStatusChanged: console.log(
    //                             buttonselect.status == Loader.Ready) //加载的状态，加载是否成功
    //        onLoaded: console.log("Loaded") //记载成功后调用
    //    }
    //    //外部链接信号的方法
    //    Connections {
    //        //buttonselect.item返回加载的qml文件的根元素
    //        target: buttonselect.item
    //        onClicked: {

    //        }
    //    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        clip: false

        Rectangle {
            id: rectangle
            x: 55
            y: 97
            width: 180
            height: 64
            color: "#ffffff"
        }
        //        onClicked: {

        //        }
    }

    TextEdit {
        id: textEdit
        text: qsTr("Enter some text...")
        selectionColor: "#308000"
        font.family: "Arial"
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
    TextEdit {
        id: textEdit2

        text: qsTr("Enter some text...")
        anchors.rightMargin: 23
        anchors.bottomMargin: 80
        anchors.leftMargin: 23
        anchors.topMargin: 201
        anchors.fill: parent
    }
}
