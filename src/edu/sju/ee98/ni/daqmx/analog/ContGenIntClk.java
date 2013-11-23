/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.sju.ee98.ni.daqmx.analog;

import edu.sju.ee98.ni.daqmx.NativeUtils;
import edu.sju.ee98.ni.daqmx.config.NIClkTiming;
import edu.sju.ee98.ni.daqmx.config.NIVoltageChan;
import edu.sju.ee98.ni.daqmx.data.NIWaveData;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Leo
 */
public class ContGenIntClk extends AnalogWave {

    private long nativeStruct;

    private native void construct();

    private native void destruct();

    static {
        try {
            NativeUtils.loadLibraryFromJar("libDAQ");
        } catch (IOException ex) {
            Logger.getLogger(ContGenIntClk.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public ContGenIntClk(NIVoltageChan voltageChan, NIClkTiming clkTiming, double[] data) {
        super(voltageChan, clkTiming);
        this.construct();
        this.data = data;
    }

    @Override
    protected void finalize() throws Throwable {
        this.destruct();
        super.finalize();
    }

    public void write() {
        contGenIntClk(
                voltageChan.getPhysicalChannel(), voltageChan.getMinVoltage(), voltageChan.getMaxVoltage(),
                clkTiming.getRate(), clkTiming.getLength(),
                this.data);
    }

    private native int contGenIntClk(String physicalChannel, double minVoltage, double maxVoltage, double rate, long length, double[] data);

    public native void start();

    public native void stop();

    @Override
    public double[] getData() {
        return this.data;
    }

    @Override
    public double getRate() {
        return this.clkTiming.getRate();
    }
}
