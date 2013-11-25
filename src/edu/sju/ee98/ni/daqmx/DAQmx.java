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

    //**************************************************************************
    //1092*** Values for the Data Layout parameter of DAQmxWriteAnalogF64, DAQmxWriteBinaryI16, DAQmxWriteDigitalU8, DAQmxWriteDigitalU32, DAQmxWriteDigitalLines ***
    public static final boolean DAQmx_Val_GroupByChannel = false;
    public static final boolean DAQmx_Val_GroupByScanNumber = true;
    //1156*** Value for the Terminal Config parameter of DAQmxCreateAIVoltageChan, DAQmxCreateAICurrentChan and DAQmxCreateAIVoltageChanWithExcit ***
    public static final int DAQmx_Val_Cfg_Default = -1;
    public static final int DAQmx_Val_Volts = 10348;
    //1281*** Value set AcquisitionType ***
    public static final int DAQmx_Val_FiniteSamps = 10178;
    public static final int DAQmx_Val_ContSamps = 10123;
    public static final int DAQmx_Val_HWTimedSinglePoint = 12522;
    //1544*** Value set Edge1 ***
    public static final int DAQmx_Val_Rising = 10280;
    public static final int DAQmx_Val_Falling = 10171;
    //**************************************************************************

    static {
        try {
            NativeUtils.loadLibraryFromJar("libDAQ");
        } catch (IOException ex) {
            Logger.getLogger(DAQmx.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private long nativeStruct;

    private native void nDAQmx(String taskName);

    public DAQmx(String taskName) {
        nDAQmx(taskName);
    }

    private native void nfinalize();

    @Override
    protected void finalize() throws Throwable {
        this.nfinalize();
        super.finalize();
    }

    //**************************************************************************
    protected native boolean isAlive();

    //Channel Configuration/Creation
    private native void createAIVoltageChan(String physicalChannel, String nameToAssignToChannel, int terminalConfig, double minVal, double maxVal, int units, String customScaleName) throws Exception;

    //Timing
    private native void cfgSampClkTiming(String source, double rate, int activeEdge, int sampleMode, long sampsPerChan) throws Exception;

    //2211 Task Configuration/Control
    //2220
    private native void startTask() throws Exception;

    private native void stopTask() throws Exception;

    private native void clearTask() throws Exception;

    //2402 Read Data
    private native int readAnalogF64(int numSampsPerChan, double timeout, boolean fillMode, double readArray[], int arraySizeInSamps, Boolean reserved) throws Exception;

    //Test----------------------------------------------------------------------
    private native void test();

    public static void main(String[] args) throws LoadLibraryException {

        DAQmx daQmx;
        daQmx = new DAQmx("");
        try {
            //******************************************************************
            // DAQmx Configure Code
            daQmx.createAIVoltageChan("Dev1/ai1", "", DAQmx_Val_Cfg_Default, -10.0, 10.0, DAQmx_Val_Volts, null);
            daQmx.cfgSampClkTiming("", 10000.0, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, 1000);

            //******************************************************************
            // DAQmx Start Code
            daQmx.startTask();

            //******************************************************************
            // DAQmx Read Code
            double data[] = new double[1000];
            daQmx.readAnalogF64(1000, 10, DAQmx_Val_GroupByChannel, data, 1000, null);

            for (int i = 0; i < data.length; i++) {
                System.out.print(data[i] + "\t");
            }
            System.out.println();

        } catch (Exception ex) {
            Logger.getLogger(DAQmx.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            try {
                if (daQmx.isAlive()) {
                    System.out.println("yyy");
                    daQmx.stopTask();
                    daQmx.clearTask();
                }
            } catch (Exception ex) {
                Logger.getLogger(DAQmx.class.getName()).log(Level.SEVERE, null, ex);
            }
        }

//        daQmx.test();
        daQmx = null;
        System.gc();
    }
}
