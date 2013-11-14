/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.sju.ee98.ni.daqmx.analog;

import edu.sju.ee98.ni.daqmx.config.NIClkTiming;
import edu.sju.ee98.ni.daqmx.config.NIVoltageChan;
import edu.sju.ee98.ni.daqmx.data.NIWaveData;
import org.apache.commons.math3.complex.Complex;
import org.apache.commons.math3.transform.DftNormalization;
import org.apache.commons.math3.transform.FastFourierTransformer;
import org.apache.commons.math3.transform.TransformType;

/**
 *
 * @author Leo
 */
public abstract class AnalogWave implements NIWaveData {

    protected NIVoltageChan voltageChan;
    protected NIClkTiming clkTiming;
    protected double[] data;

    public AnalogWave(NIVoltageChan voltageChan, NIClkTiming clkTiming) {
        this.voltageChan = voltageChan;
        this.clkTiming = clkTiming;
    }

    public Complex getMainFrequency(double frequency) {
        FastFourierTransformer fft = new FastFourierTransformer(DftNormalization.STANDARD);
        Complex[] transform = fft.transform(data, TransformType.FORWARD);
        int mainF = (int) (frequency * this.clkTiming.getLength() / this.clkTiming.getRate());
        return transform[mainF];
    }
}
