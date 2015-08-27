package main

import (
	"fmt"
	"github.com/sbinet/go-gnuplot"
	"math/rand"
	"os"
	"strconv"
	"time"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func main() {
	filename := "/mnt/tmpDisk/xchg.txt"
	var file *os.File
	var err error
	var neuronNumber, clickNumber, iterationNumber int64
	RAND := rand.New(rand.NewSource(time.Now().UnixNano()))

	file, err = os.OpenFile(filename, os.O_RDWR|os.O_CREATE|os.O_TRUNC, 0640)
	check(err)
	defer file.Close()

	plotname := ""
	persist := false
	debug := false
	plot, err := gnuplot.NewPlotter(plotname, persist, debug)
	check(err)
	defer plot.Close()

	plot.CheckedCmd("reset")
	plot.CheckedCmd("set term gif size 800,400 delay 100")
	plot.CheckedCmd("set term X11")
	//plot.CheckedCmd("set output \"animate.gif\"")
	plot.CheckedCmd("set cbrange [0:1]")
	//plot.CheckedCmd("set zrange [-1:1]")
	//plot.CheckedCmd("set palettergb formulae 22,13,-31") // yet another rainbow palette: from blue(0) to red(1).
	plot.CheckedCmd("set palette defined( 0       0.2314  0.2980  0.7529, 0.03125 0.2667  0.3529  0.8000, 0.0625  0.3020  0.4078  0.8431, 0.09375 0.3412  0.4588  0.8824, 0.125   0.3843  0.5098  0.9176, 0.15625 0.4235  0.5569  0.9451, 0.1875  0.4667  0.6039  0.9686, 0.21875 0.5098  0.6471  0.9843, 0.25    0.5529  0.6902  0.9961, 0.28125 0.5961  0.7255  1.0000, 0.3125  0.6392  0.7608  1.0000, 0.34375 0.6824  0.7882  0.9922, 0.375   0.7216  0.8157  0.9765, 0.40625 0.7608  0.8353  0.9569, 0.4375  0.8000  0.8510  0.9333, 0.46875 0.8353  0.8588  0.9020, 0.5     0.8667  0.8667  0.8667, 0.53125 0.8980  0.8471  0.8196, 0.5625  0.9255  0.8275  0.7725, 0.59375 0.9451  0.8000  0.7255, 0.625   0.9608  0.7686  0.6784, 0.65625 0.9686  0.7333  0.6275, 0.6875  0.9686  0.6941  0.5804, 0.71875 0.9686  0.6510  0.5294, 0.75    0.9569  0.6039  0.4824, 0.78125 0.9451  0.5529  0.4353, 0.8125  0.9255  0.4980  0.3882, 0.84375 0.8980  0.4392  0.3451, 0.875   0.8706  0.3765  0.3020, 0.90625 0.8353  0.3137  0.2588, 0.9375  0.7961  0.2431  0.2196, 0.96875 0.7529  0.1569  0.1843, 1       0.7059  0.0157  0.1490) ")
	plot.CheckedCmd("set xrange [0:100]")
	plot.CheckedCmd("set yrange [0:400]")
	plot.CheckedCmd("set zrange [0:1]")
	plot.SetXLabel("my X data")
	plot.SetYLabel("my Y data")
	plot.SetZLabel("my Z data")
	plot.CheckedCmd("set view map")
	//plot.CheckedCmd("set object 1 rect from graph 0, graph 0 to graph 1, graph 1 back")
	//plot.CheckedCmd("set object 1 rect fc rgb \"black\" fillstyle solid 1.0")

	for iterationNumber = 0; iterationNumber < 100; iterationNumber++ { // suppose 100 neurons
		file, err = os.OpenFile(filename, os.O_RDWR|os.O_CREATE|os.O_TRUNC, 0640)
		for neuronNumber = 0; neuronNumber < 100; neuronNumber++ { // suppose 100 neurons
			for clickNumber = 0; clickNumber < 400; clickNumber++ { // No.? time step
				_, err = file.Write([]byte(strconv.FormatFloat(float64(neuronNumber), 'f', 15, 64)))
				_, err = file.WriteString("  ")
				_, err = file.Write([]byte(strconv.FormatFloat(float64(clickNumber), 'f', 15, 64)))
				_, err = file.WriteString("  ")
				_, err = file.Write([]byte(strconv.FormatFloat(RAND.Float64(), 'f', 15, 64)))
				_, err = file.WriteString("\n")
			}
		}
		fmt.Printf("Plotted [%3v th] iteration\n", iterationNumber+1)
		file.Sync()
		file.Close()
		plot.CheckedCmd("splot \"%v\" u 1:2:3 w p ps 0.5 pt 7 palette notitle", filename)
		time.Sleep(250 * time.Millisecond)
	}

	fmt.Println("gnuplot finished.")
	plot.CheckedCmd("set output")
	plot.CheckedCmd("replot")
	plot.CheckedCmd("quit")
	return
}
