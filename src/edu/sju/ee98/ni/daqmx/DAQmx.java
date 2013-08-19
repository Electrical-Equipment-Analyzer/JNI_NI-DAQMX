package edu.sju.ee98.ni.daqmx;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Leo
 */
public class DAQmx {

    static {
        System.loadLibrary("libs/libDataAcquisitionNative");
    }

    public DAQmx() {
    }

    public native void print();

    public native double[] acqIntClk();

    public  native double[] acqIntClk(double minVoltage, double maxVoltage, double rate, long length);


    private void callback() {
        System.out.println("In Java");
    }

    public static void main(String[] args) {
        DAQmx daQmx = new DAQmx();
        daQmx.print();
//        double[] acqIntClk = daQmx.acqIntClk();
//        for (int i = 0; i < acqIntClk.length; i++) {
//            System.out.print(acqIntClk[i] + "\t");
//        }
    }
}
