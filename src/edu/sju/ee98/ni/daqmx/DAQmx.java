package edu.sju.ee98.ni.daqmx;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

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
            NativeUtils.loadLibraryFromJar("libDAQ");
//            System.loadLibrary("../DataAcquisitionNative/dist/Debug/MinGW_TDM-Windows/libDataAcquisitionNative");
        } catch (java.lang.UnsatisfiedLinkError err) {
            throw new LoadLibraryException(err.getMessage());
        } catch (IOException ex) {
            Logger.getLogger(DAQmx.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public native void print();

    public native double[] acqIntClk(String physicalChannel, double minVoltage, double maxVoltage, double rate, long length);

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
