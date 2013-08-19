/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.sju.ee98.ni.daqmx.data;

import edu.sju.ee98.ni.daqmx.DAQmx;
import edu.sju.ee98.ni.daqmx.NIAnalogConfig;

/**
 *
 * @author Leo
 */
public class AnalogWave implements java.io.Serializable {

    private NIAnalogConfig config;
    private double[] data;

    public AnalogWave(NIAnalogConfig config) {
        this.config = config;
    }

    public void read() {
        this.data = new DAQmx().acqIntClk(config.getMinVoltage(), config.getMaxVoltage(), config.getRate(), config.getLength());
    }

    public double[] getData() {
        return data;
    }
}
