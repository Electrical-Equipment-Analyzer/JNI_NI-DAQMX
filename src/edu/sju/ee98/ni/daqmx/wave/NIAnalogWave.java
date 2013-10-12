/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.sju.ee98.ni.daqmx.wave;

import edu.sju.ee98.ni.daqmx.DAQmx;
import edu.sju.ee98.ni.daqmx.LoadLibraryException;
import edu.sju.ee98.ni.daqmx.config.NIAnalogConfig;
import edu.sju.ee98.ni.daqmx.data.NIWaveData;
import java.util.Arrays;

/**
 *
 * @author Leo
 */
public class NIAnalogWave implements NIWaveData {

    private NIAnalogConfig config;
    private double[] data;

    public NIAnalogWave(NIAnalogConfig config) {
        this.config = config;
    }

    public void read() throws LoadLibraryException {
        this.data = new DAQmx().acqIntClk(config.getPhysicalChannel(), config.getMinVoltage(), config.getMaxVoltage(), config.getRate(), config.getLength());
    }

    @Override
    public double[] getData() {
        return this.data;
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
