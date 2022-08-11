import sys
from PyQt5.QtGui import QPainter, QPen
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5.QtChart import QChart, QChartView, QPieSeries, QPieSlice


class DemoChartPieSeries(QMainWindow):
    def __init__(self, parent=None):
        super(DemoChartPieSeries, self).__init__(parent)

        # 设置窗口标题
        self.setWindowTitle('实战 Qt for Python: QChart饼图演示')
        # 设置窗口大小
        self.resize(480, 360)
        self.createChart()

    def createChart(self):
        # 设置饼图数据
        pieSeries = QPieSeries()
        pieSeries.append('Jane', 1)
        pieSeries.append('Joe', 2)
        pieSeries.append('Andy', 3)
        pieSeries.append('Barbara', 4)
        pieSeries.append('Axel', 5)

        # 处理索引号为1的片
        pieSlice = pieSeries.slices()[1]
        pieSlice.setExploded()
        # pieSlice.setLabelVisible()  # 设置标签可见,缺省不可见
        pieSlice.setPen(QPen(Qt.darkGreen, 2))
        pieSlice.setBrush(Qt.green)

        # 创建图表
        chart = QChart()
        chart.addSeries(pieSeries)
        chart.setTitle('简单的饼图示例')
        chart.legend().hide()

        chart.legend().setVisible(True)
        chart.legend().setAlignment(Qt.AlignBottom)

        # 图表视图
        chartView = QChartView(chart)
        chartView.setRenderHint(QPainter.Antialiasing)

        self.setCentralWidget(chartView)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = DemoChartPieSeries()
    window.show()
    sys.exit(app.exec())   