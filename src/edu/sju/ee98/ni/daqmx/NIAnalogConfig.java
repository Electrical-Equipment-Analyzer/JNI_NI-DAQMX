/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.sju.ee98.ni.daqmx;

/**
 *
 * @author Leo
 */
public class NIAnalogConfig implements java.io.Serializable {

    private double minVoltage;
    private double maxVoltage;
    private double rate;
    private long length;

    public NIAnalogConfig(double minVoltage, double maxVoltage, double rate, long length) {
        this.minVoltage = minVoltage;
        this.maxVoltage = maxVoltage;
        this.rate = rate;
        this.length = length;
    }

    public double getMinVoltage() {
        return minVoltage;
    }

    public double getMaxVoltage() {
        return maxVoltage;
    }

    public double getRate() {
        return rate;
    }

    public long getLength() {
        return length;
    }

    @Override
    public String toString() {
        return "NIAnalogConfig{" + "minVoltage=" + minVoltage + ", maxVoltage=" + maxVoltage + ", rate=" + rate + ", length=" + length + '}';
    }
}
