/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.sju.ee98.ni.daqmx.data;

import edu.sju.ee98.ni.daqmx.DAQmx;
import edu.sju.ee98.ni.daqmx.LoadLibraryException;
import edu.sju.ee98.ni.daqmx.NIAnalogConfig;
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

    public void gen(int length, double a, double b) {
        data = new double[length];
        for (int x = 0; x < data.length; x++) {
            data[x] = Math.sin(b * x) * a;
        }
    }

    public void read() throws LoadLibraryException {
        this.data = new DAQmx().acqIntClk(config.getMinVoltage(), config.getMaxVoltage(), config.getRate(), config.getLength());
    }

    @Override
    public double[] getData() {
        return data;
    }

    @Override
    public String toString() {
        return "AnalogWave{" + "config=" + config + ", data=" + Arrays.toString(data) + '}';
    }
}
