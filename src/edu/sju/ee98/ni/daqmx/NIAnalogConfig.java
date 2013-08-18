/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.sju.ee98.ni.daqmx;

/**
 *
 * @author Leo
 */
public class NIAnalogConfig {

    private int voltage;
    private float rate;
    private int length;

    public NIAnalogConfig(int voltage, float rate, int length) {
        this.voltage = voltage;
        this.rate = rate;
        this.length = length;
    }

    public int getVoltage() {
        return voltage;
    }

    public float getRate() {
        return rate;
    }

    public int getLength() {
        return length;
    }

    @Override
    public String toString() {
        return "NIAnalogConfig{" + "voltage=" + voltage + ", rate=" + rate + ", length=" + length + '}';
    }
}
