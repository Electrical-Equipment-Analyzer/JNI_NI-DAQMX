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

    public DAQmx() throws LoadLibraryException {
        try {
            System.loadLibrary("../DataAcquisitionNative/dist/Debug/MinGW_TDM-Windows/libDataAcquisitionNative");
        } catch (java.lang.UnsatisfiedLinkError err) {
            throw new LoadLibraryException(err.getMessage());
        }
    }

    public native void print();

    public native double[] acqIntClk();

    public native double[] acqIntClk(double minVoltage, double maxVoltage, double rate, long length);

    private void callback() {
        System.out.println("In Java");
    }

    public static void main(String[] args) throws LoadLibraryException {
        DAQmx daQmx = new DAQmx();
        daQmx.print();
//        double[] acqIntClk = daQmx.acqIntClk();
//        for (int i = 0; i < acqIntClk.length; i++) {
//            System.out.print(acqIntClk[i] + "\t");
//        }
    }
}
