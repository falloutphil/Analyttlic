
import wx
import wx.lib.plot as plot

 

class MyFrame(wx.Frame):
    def __init__(self, data, origData, yieldCurve):
        self.frame1 = wx.Frame(None, title="Analyttlic", id=-1, size=(800, 600))
        self.panel1 = wx.Panel(self.frame1)
        #self.panel1.SetBackgroundColour("yellow")

        # mild difference between wxPython26 and wxPython28
        if wx.VERSION[1] < 7:
            plotter = plot.PlotCanvas(self.panel1, size=(800, 600))
        else:
            plotter = plot.PlotCanvas(self.panel1)
            plotter.SetInitialSize(size=(800, 600))

        # enable the zoom feature (drag a box around area of interest)
        plotter.SetEnableZoom(True)


        # list of (x,y) data point tuples
        # data = [(1,2), (2,3), (3,5), (4,6), (5,8), (6,8), (12,10), (13,4)]

        # draw points as a line
        line = plot.PolyLine(data, colour='red', width=1)
        origLine = plot.PolyLine(origData, colour='blue', width=1)  
        # also draw markers, default colour is black and size is 2
        # other shapes 'circle', 'cross', 'square', 'dot', 'plus'
        marker = plot.PolyMarker(origData, marker='cross')
        yieldLine = plot.PolyLine(yieldCurve, colour='green', width=1)
        # set up text, axis and draw
        gc = plot.PlotGraphics([line, origLine, marker, yieldLine], 'Forward Rates Curve', 'Time (years)', 'Forward Rate (%)')
        plotter.Draw(gc, xAxis=(0,20), yAxis=(0,20))

        self.frame1.Show(True)

 

 

