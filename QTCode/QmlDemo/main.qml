import QtQuick 2.6
import QtQuick.Window 2.2
import "demourl"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    id: rooot
    property int count: 0;
    property Component component1: null;
    MainForm {
        mouseArea.onDoubleClicked: {
}
        anchors.fill: parent
        mouseArea.onClicked: {
            console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
//            chang()
            add()

        }
        textEdit2.text: currentDateTime.getCurrentDateTime2();
    }

    Loader{
        id: buttonselect
        x: 200
        y:300
        focus: true
    }


    function chang(){
        buttonselect.source="button.qml"
    }
//外部链接信号的方法
    Connections{
        //buttonselect.item返回加载的qml文件的根元素
        target: buttonselect.item
        onClicked:{
            status.text="it is clicked!"
        }
    }

    Keys.onPressed: {
        console.log("Captured: ", event.text);
        event.accepted = true;
    }
    //点击按钮动态生成组件
    function add() {
        if(rooot.component1==null)
        {
            rooot.component1 = Qt.createComponent("button.qml")
        }
        if(rooot.component1.status==Component.Ready)
        {
            //第一个参数是parent，第二个参数是object的属性设置
            var object=rooot.component1.createObject(rooot,{"x" : 10, "y" : 10});//注意：createObject函数并不能共通过智能提示给出
            object.x=(object.width+10)*rooot.count;
            console.log(qsTr('===:'+object.x))
            rooot.count++;
            if(rooot.count % 2 == 1) {
                object.destroy(1000);
            }

        }
    }

//    Button2 {
//        id:button1
//        x:12
//        y:12
//        text:"tart"
//        onClicked:{
//            status.text="it is clicked!"
//        }
//    }




    Text {
        id: status
        y:76
        width:116
        x:12
        height: 26
        text: qsTr("wait...")
        horizontalAlignment: Text.AlignHCenter
    }
}
