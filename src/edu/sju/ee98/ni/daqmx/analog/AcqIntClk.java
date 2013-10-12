/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.sju.ee98.ni.daqmx.analog;

import edu.sju.ee98.ni.daqmx.LoadLibraryException;
import edu.sju.ee98.ni.daqmx.config.NIClkTiming;
import edu.sju.ee98.ni.daqmx.config.NIVoltageChan;
import edu.sju.ee98.ni.daqmx.data.NIWaveData;

/**
 *
 * @author Leo
 */
public class AcqIntClk implements NIWaveData {

    private NIVoltageChan voltageChan;
    private NIClkTiming clkTiming;
    private double[] data;

    public AcqIntClk(NIVoltageChan voltageChan, NIClkTiming clkTiming) {
        this.voltageChan = voltageChan;
        this.clkTiming = clkTiming;
    }

    public void read() throws LoadLibraryException {
        try {
            System.loadLibrary("lib/libDataAcquisitionNative");
        } catch (java.lang.UnsatisfiedLinkError err) {
            throw new LoadLibraryException(err.getMessage());
        }
        this.data = acqIntClk(
                voltageChan.getPhysicalChannel(), voltageChan.getMinVoltage(), voltageChan.getMaxVoltage(),
                clkTiming.getRate(), clkTiming.getSampsPerChanToAcquire());
    }

    private native double[] acqIntClk(String physicalChannel, double minVoltage, double maxVoltage, double rate, long sampsPerChanToAcquire);

    @Override
    public double[] getData() {
        return this.data;
    }

    @Override
    public double getRate() {
        return this.clkTiming.getRate();
    }
}
