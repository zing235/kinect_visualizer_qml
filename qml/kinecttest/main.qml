//import QtQuick 2.0
//import KinectCamera 1.0
//import QtQuick.Controls 1.1
//Rectangle {
//    id: rectangle2
//    width: 800
//    height: 600

//KinectCamera{
//    id:testcamera
//    anchors.rightMargin: 0
//    anchors.bottomMargin: 0
//    anchors.leftMargin: 0
//    anchors.topMargin: 0
//    anchors.fill: parent
//            Timer{
//                id:updateview
//                interval: 1
//                repeat: true
//                running: true
//                onTriggered: {
//                    time.text = Date().toString()
//                    testcamera.updatecamera()
//                     }
//                }
//                Button{
//                    id:closecamera
//                    width: 82
//                    height: 23
//                    text: "关闭kinect"
//                    anchors.left: parent.left
//                    anchors.leftMargin: 0
//                    anchors.top: parent.top
//                    anchors.topMargin: 0
//                    onClicked:testcamera.closecamera()
//               }
//                Text {
//                    id: time
//                    x: 318
//                    height: 20
//                    text: "time"
//                    anchors.right: parent.right
//                    anchors.rightMargin: 0
//                    anchors.top: parent.top
//                    anchors.topMargin: 0
//                    style: Text.Raised
//                    font.pointSize: 15
//               }
//           }
//}




import KinectCamera 1.0
import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
Rectangle {
    id: rectangle1
    width: 800
    height: 600

    ColumnLayout {
        id: columnLayout1
        width: rectangle1.width*2/5
        spacing: 50
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 8

        Rectangle {
            id: rectangle2
            height: rectangle1.height*14/30
            color: "#c92c2c"
            border.color: "#d2c1c1"
            anchors.right: parent.right
            anchors.rightMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 8

            Rectangle {
                id: rectangle6
                x: 48
                y: 72
                height: rectangle1.height*12/30
                color: "#ffffff"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 8
                anchors.right: parent.right
                anchors.rightMargin: 8
                anchors.left: parent.left
                anchors.leftMargin: 8
                KinectCamera{
                    id:testcamera
                    streamsource:"depth"
                    anchors.rightMargin: 0
                    anchors.bottomMargin: 0
                    anchors.leftMargin: 0
                    anchors.topMargin: 0
                    anchors.fill: parent
                    Timer{
                        id:updateview
                        interval: 1
                        repeat: true
                        running: true
                        onTriggered: {
                            time.text = Date().toString()
                            testcamera.updatecamera()
                        }
                    }
                    Button{
                        id:closecamera
                        width: 82
                        height: 23
                        text: "关闭kinect"
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        onClicked:testcamera.closecamera()
                    }
                    Text {
                        id: time
                        x: 318
                        height: 20
                        text: "time"
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        style: Text.Raised
                        font.pointSize: 18
                    }
                }
            }

            Rectangle {
                id: rectangle4
                height: rectangle1.height/30
                color: "#ffffff"
                radius: 8
                anchors.right: parent.right
                anchors.rightMargin: 40
                anchors.left: parent.left
                anchors.leftMargin: 40
                anchors.top: parent.top
                anchors.topMargin: 8

                Text {
                    id: text1
                    color: "#f30707"
                    anchors.centerIn: parent
                    text: qsTr("depth camera")
                    font.pixelSize: 16
                }
        }

        }

        Rectangle {
            id: rectangle3
            y: 362
            height: rectangle1.height*14/30
            color: "#c92c2c"
            anchors.right: parent.right
            anchors.rightMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            Rectangle {
                id: rectangle8
                x: 48
                y: 72
                height: rectangle1.height*12/30
                color: "#ffffff"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 8
                anchors.right: parent.right
                anchors.rightMargin: 8
                anchors.left: parent.left
                anchors.leftMargin: 8
                KinectCamera{
                    id:testcamera2
                    streamsource:"color"
                    anchors.rightMargin: 0
                    anchors.bottomMargin: 0
                    anchors.leftMargin: 0
                    anchors.topMargin: 0
                    anchors.fill: parent
                    Timer{
                        id:updateview2
                        interval: 1
                        repeat: true
                        running: true
                        onTriggered: {
                            time2.text = Date().toString()
                            testcamera2.updatecamera()
                        }
                    }
                    Button{
                        id:closecamera2
                        width: 82
                        height: 23
                        text: "关闭kinect"
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        onClicked:testcamera2.closecamera()
                    }
                    Text {
                        id: time2
                        x: 318
                        height: 20
                        text: "time"
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        style: Text.Raised
                        font.pointSize: 18
                    }
                }
            }
            Rectangle {
                id: rectangle5
                height: rectangle1.height/30
                color: "#ffffff"
                radius: 8
                anchors.right: parent.right
                anchors.rightMargin: 40
                anchors.left: parent.left
                anchors.leftMargin: 40
                anchors.top: parent.top
                anchors.topMargin: 8

                Text {
                    id: text2
                    color: "#f30707"
                    anchors.centerIn: parent
                    text: qsTr("color camera")
                    font.pixelSize: 16
                }
        }
    }

}
    ColumnLayout {
        id: columnLayout3
        anchors.left: columnLayout1.right
        anchors.rightMargin: 0
        anchors.right: columnLayout2.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 8
        Rectangle{
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 8
            height: rectangle1.height*14/30
            Image {
                id: arrow1
                x: 26
                y: 271
                anchors.verticalCenterOffset: 146
                anchors.horizontalCenterOffset: 0
                source: "arrow.png"
                anchors.centerIn: parent
            }

        }
        Rectangle{
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.topMargin: 8
            height: rectangle1.height*14/30
        }


    }
    ColumnLayout {
        id: columnLayout2
        width: rectangle1.width*14/30
        anchors.right:  parent.right
        anchors.rightMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 8
        Rectangle {
            id: rectangle9
            height: rectangle1.height*28/30
            color: "#c92c2c"
            border.color: "#d2c1c1"
            anchors.right: parent.right
            anchors.rightMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 8
            Timer{
                id: sbvaluetimer
                interval:30000
                repeat: true
                running: true
                onTriggered: {
                    imagevalue.getSbImageValue();
                }
            }
            Column{
                anchors.fill: parent
//                width: parent.width
                spacing: 5

            Rectangle{

                width: parent.width
                height: 45
                color: "#000000"
               Text{
                    anchors.centerIn: parent
                    text: "泡沫特征"
                    font.pixelSize:40
                    font.italic: true
                    color: "#00FFFF"
                }
            }
            Rectangle{
                id:sbtezheng
                width: parent.width
                height: (parent.height-75)/6
                color: "#000000"
               Text{
                    id:sbbubblesize
                    anchors.centerIn: parent
                    text: "泡沫大小: " +imagevalue.sbBubbleSize
                    font.pixelSize:30
                    font.italic: true
                    color: "#00FF00"
                }
            }
            Rectangle{
                width: parent.width
                height: sbtezheng.height
                color: "#000000"
               Text{
                    id:sbbubblenumber
                    anchors.centerIn: parent
                    text: "泡沫个数: "+imagevalue.sbBubbleNumber
                    font.pixelSize:30
                    font.italic: true
                    color: "#00FF00"
                }
            }
            Rectangle{
                width: parent.width
                height: sbtezheng.height
                color: "#000000"
               Text{
                    id:sbgraymean
                    anchors.centerIn: parent
                    text: "泡沫颜色: "+imagevalue.sbGrayMean
                    font.pixelSize:30
                    font.italic: true
                    color: "#00FF00"
                }
            }
            Rectangle{
                width: parent.width
                height: sbtezheng.height
                color: "#000000"
               Text{
                    id:sbbubblefangcha
                    anchors.centerIn: parent
//                    text: "泡沫方差"
                    text: "液位" +imagevalue.sbLevel
                    font.pixelSize:30
                    font.italic: true
                    color: "#00FF00"
                }
            }
            Rectangle{
                width: parent.width
                height: sbtezheng.height
                color: "#000000"
               Text{
                    id:sbchengzailv
                    anchors.centerIn: parent
                    text: "承载率"
                    font.pixelSize:30
                    font.italic: true
                    color: "#00FF00"
                }
            }
            Rectangle{
                width: parent.width
                height: sbtezheng.height
                color: "#000000"
               Text{
                    id:sbbubblerate
                    anchors.centerIn: parent
                    text: "泡沫速度"
                    font.pixelSize:30
                    font.italic: true
                    color: "#00FF00"
                }
            }


            }



        }

}

}

