package edu.sju.ee.eea.jni.daqmx;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import tw.edu.sju.ee.commons.nativeutils.NativeUtils;

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
        try {
            NativeUtils.loadLibraryFromJar("jni_DAQmx");
        } catch (IOException ex) {
            Logger.getLogger(DAQmx.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    //**************************************************************************
    //Java Object
    private long nativeStruct;

    public DAQmx() {
        construct();
    }

    @Override
    protected void finalize() throws Throwable {
        this.destruct();
        super.finalize();
    }

    //**************************************************************************
    //Native Object
    private native void construct();

    private native void destruct();

    public native boolean isAlive();

    //**************************************************************************
    //1062***Non-Attribute Function Parameter Values***
    public static final int Val_Acquired_Into_Buffer = 1;
    public static final int Val_Transferred_From_Buffer = 2;
    //1092*** Values for the Data Layout parameter of DAQmxWriteAnalogF64, DAQmxWriteBinaryI16, DAQmxWriteDigitalU8, DAQmxWriteDigitalU32, DAQmxWriteDigitalLines ***
    public static final boolean Val_GroupByChannel = false;
    public static final boolean Val_GroupByScanNumber = true;
    //1156*** Value for the Terminal Config parameter of DAQmxCreateAIVoltageChan, DAQmxCreateAICurrentChan and DAQmxCreateAIVoltageChanWithExcit ***
    public static final int Val_Cfg_Default = -1;
    public static final int Val_Volts = 10348;
    //1281*** Value set AcquisitionType ***
    public static final int Val_FiniteSamps = 10178;
    public static final int Val_ContSamps = 10123;
    public static final int Val_HWTimedSinglePoint = 12522;
    //1544*** Value set Edge1 ***
    public static final int Val_Rising = 10280;
    public static final int Val_Falling = 10171;

    //1770*** Values for DAQmx_Dev_ProductCategory ***
    //1771*** Value set ProductCategory ***
    public static final int Val_CSeriesModule = 14659;
    public static final int Val_SCXIModule = 14660;

    //**************************************************************************
    //2211 Task Configuration/Control
    public native void createTask(String taskName) throws Exception;

    public native void startTask() throws Exception;

    public native void stopTask() throws Exception;

    public native void clearTask() throws Exception;

    public native String getNthTaskDevice(int index);

    public native void registerEveryNSamplesEvent(int everyNsamplesEventType, int nSamples, int options);

    public native void registerDoneEvent(int options);

    //**************************************************************************
    //2245Channel Configuration/Creation
    public native void createAIVoltageChan(String physicalChannel, String nameToAssignToChannel, int terminalConfig, double minVal, double maxVal, int units, String customScaleName) throws Exception;

    public native void createAOVoltageChan(String physicalChannel, String nameToAssignToChannel, double minVal, double maxVal, int units, String customScaleName);

    //**************************************************************************
    //2375 Triggering
    public native void cfgDigEdgeStartTrig(String triggerSource, int triggerEdge);

    //**************************************************************************
    //2402 Read Data
    public native int readAnalogF64(int numSampsPerChan, double timeout, boolean fillMode, double readArray[], int arraySizeInSamps, Boolean reserved) throws Exception;

    //2453Write Data
    public native void writeAnalogF64(int numSampsPerChan, boolean autoStart, double timeout, boolean dataLayout, double writeArray[]);

    //5072********** Device **********
    public native int getDevProductCategory(String device);

    //5517********** Task **********
    public native int getTaskNumDevices();

    //**************************************************************************
    //5531Timing
    public native void cfgSampClkTiming(String source, double rate, int activeEdge, int sampleMode, long sampsPerChan) throws Exception;

    //**************************************************************************
    //Test----------------------------------------------------------------------
    public native void test();

    //**************************************************************************
    //static
    public String getTerminalNameWithDevPrefix(String terminalName) {
        String triggerName = null;
        int i = 1;
        int numDevices = this.getTaskNumDevices();
        while (i <= numDevices) {
            String device;
            int productCategory;
            device = this.getNthTaskDevice(i++);
            productCategory = this.getDevProductCategory(device);
            if (productCategory != DAQmx.Val_CSeriesModule && productCategory != DAQmx.Val_SCXIModule) {
                triggerName = "/" + device + "/" + terminalName;
                break;
            }
        }
        return triggerName;
    }

}
