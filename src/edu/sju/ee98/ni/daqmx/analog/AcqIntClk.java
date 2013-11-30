/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.sju.ee98.ni.daqmx.analog;

import edu.sju.ee.jni.LoadLibraryException;
import edu.sju.ee.jni.NativeUtils;
import edu.sju.ee98.ni.daqmx.config.NIClkTiming;
import edu.sju.ee98.ni.daqmx.config.NIVoltageChan;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Leo
 */
public class AcqIntClk extends AnalogWave {

    static {
        try {
            NativeUtils.loadLibraryFromJar("libDAQ");
        } catch (IOException ex) {
            Logger.getLogger(AcqIntClk.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public AcqIntClk(NIVoltageChan voltageChan, NIClkTiming clkTiming) {
        super(voltageChan, clkTiming);
    }

    public void read() throws LoadLibraryException {
        this.data = acqIntClk(
                voltageChan.getPhysicalChannel(), voltageChan.getMinVoltage(), voltageChan.getMaxVoltage(),
                clkTiming.getRate(), clkTiming.getLength());
    }

    private native double[] acqIntClk(String physicalChannel, double minVoltage, double maxVoltage, double rate, long length);

    @Override
    public double[] getData() {
        return this.data;
    }

    @Override
    public double getRate() {
        return this.clkTiming.getRate();
    }

    @Override
    public String toString() {
        return "AcqIntClk{" + "voltageChan=" + voltageChan + ", clkTiming=" + clkTiming + ", data=" + data + '}';
    }
}
