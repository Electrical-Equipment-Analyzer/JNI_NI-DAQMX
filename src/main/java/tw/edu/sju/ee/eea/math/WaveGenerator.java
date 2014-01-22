/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package tw.edu.sju.ee.eea.math;

/**
 *
 * @author Leo
 */
public class WaveGenerator {

    private double[] data;
    private double rate;
    private int length;
    private double voltage;
    private double frequency;
    private double position;

    public WaveGenerator(double rate, int length, double voltage, double frequency) {
        this(rate, length, voltage, frequency, 0);
    }

    public WaveGenerator(double rate, int length, double voltage, double frequency, double position) {
        this.rate = rate;
        this.length = length;
        this.voltage = voltage;
        this.frequency = frequency;
        this.position = position;
        generate();
    }

    private void generate() {
        data = new double[length];
        for (int x = 0; x < data.length; x++) {
            data[x] = this.voltage * Math.sin((x + this.position) / this.rate * 2 * Math.PI * this.frequency);
        }
    }

    public double[] getData() {
        return this.data;
    }

    public double getRate() {
        return this.rate;
    }

    @Override
    public String toString() {
        return "WaveSimulator{" + "data=" + data + ", rate=" + rate + ", length=" + length + ", voltage=" + voltage + ", frequency=" + frequency + '}';
    }
}
