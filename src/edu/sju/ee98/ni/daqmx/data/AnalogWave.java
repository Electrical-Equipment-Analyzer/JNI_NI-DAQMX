/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.sju.ee98.ni.daqmx.data;

import edu.sju.ee98.ni.daqmx.DAQmx;
import edu.sju.ee98.ni.daqmx.LoadLibraryException;
import edu.sju.ee98.ni.daqmx.config.NIAnalogConfig;
import java.awt.Graphics;
import java.util.Arrays;

/**
 *
 * @author Leo
 */
public class AnalogWave implements WaveData {

    private NIAnalogConfig config;
    private double[] data;

    public AnalogWave(NIAnalogConfig config) {
        this.config = config;
    }

//    public static void main(String[] args) {
//        System.out.println(Math.si);
//    }
    public void gen() {
        data = new double[(int) config.getLength()];
        for (int x = 0; x < data.length; x++) {
            data[x] = Math.sin(x / config.getRate() * 2 * Math.PI * config.getMinVoltage()) * config.getMaxVoltage();
        }
    }

    public void read() throws LoadLibraryException {
        this.data = new DAQmx().acqIntClk(config.getPhysicalChannel(), config.getMinVoltage(), config.getMaxVoltage(), config.getRate(), config.getLength());
    }

    @Override
    public double[] getData() {
        return data;
    }

//    @Override
//    public double[] getDoubleArray() {
//        return data;
//    }
    @Override
    public void paintWave(Graphics g, Grid grid) {
        grid.paintWave(g, this.getRate(), this.data);
    }

    @Override
    public double getRate() {
        return this.config.getRate();
    }

    @Override
    public String toString() {
        return "AnalogWave{" + "config=" + config + ", data=" + Arrays.toString(data) + '}';
    }
}
