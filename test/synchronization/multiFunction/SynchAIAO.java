/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package synchronization.multiFunction;

import edu.sju.ee.ni.daqmx.DAQmx;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Leo
 */
public class SynchAIAO {

    public static void main(String[] args) {

        DAQmx handleAI = new DAQmx();
        DAQmx handleAO = new DAQmx();
        try {
            //******************************************************************
            // DAQmx Configure Code
            handleAI.createTask("");
            handleAI.createAIVoltageChan("Dev1/ai0", "", DAQmx.Val_Cfg_Default, -10.0, 10.0, DAQmx.Val_Volts, null);
            handleAI.cfgSampClkTiming("", 10000.0, DAQmx.Val_Rising, DAQmx.Val_ContSamps, 1000);
            String trigName = getTerminalNameWithDevPrefix(handleAI, "ai/StartTrigger");

            handleAO.createTask("");
            handleAO.createAOVoltageChan("Dev1/ao0", "", -10.0, 10.0, DAQmx.Val_Volts, null);
            handleAO.cfgSampClkTiming("", 5000.0, DAQmx.Val_Rising, DAQmx.Val_ContSamps, 1000);
            handleAO.cfgDigEdgeStartTrig(trigName, DAQmx.Val_Rising);

            handleAI.registerEveryNSamplesEvent(DAQmx.Val_Acquired_Into_Buffer, 1000, 0);
            handleAI.registerDoneEvent(0);

            double AOdata[] = genSineWave(1000, 2.0, 100.0 / 1000, 0);

            handleAO.writeAnalogF64(1000, false, 10.0, DAQmx.Val_GroupByChannel, AOdata);

            //******************************************************************
            // DAQmx Start Code
            handleAO.startTask();
//            Thread.sleep(10);
            handleAI.startTask();

            Thread.sleep(10000);
            //******************************************************************
            // DAQmx Read Code
//            double data[] = new double[1000];
//            handleAI.readAnalogF64(1000, 10, DAQmx.Val_GroupByChannel, data, 1000, null);
//
//            for (int i = 0; i < data.length; i++) {
//                System.out.print(data[i] + "\t");
//            }
//            System.out.println();

//            handleAI.test();
        } catch (Exception ex) {
            Logger.getLogger(SynchAIAO.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
//            try {
//                if (handle.isAlive()) {
//                    handle.stopTask();
//                    handle.clearTask();
//                }
//            } catch (Exception ex) {
//                Logger.getLogger(SynchAIAO.class.getName()).log(Level.SEVERE, null, ex);
//            }
        }
        handleAI = null;
        System.gc();
    }

    public static double[] genSineWave(int numElements, double amplitude, double frequency, double phase) {
        double sineWave[] = new double[numElements];
        for (int i = 0; i < sineWave.length; ++i) {
            sineWave[i] = amplitude * Math.sin(Math.PI / 180.0 * (phase + 360.0 * frequency * i));
        }
        phase = (phase + frequency * 360.0 * numElements) % 360;
        return sineWave;
    }

    public static String getTerminalNameWithDevPrefix(DAQmx handle, String terminalName) {
        String triggerName = null;
        int i = 1;
        int numDevices = handle.getTaskNumDevices();
        while (i <= numDevices) {
            String device;
            int productCategory;
            device = handle.getNthTaskDevice(i++);
            productCategory = handle.getDevProductCategory(device);
            if (productCategory != DAQmx.Val_CSeriesModule && productCategory != DAQmx.Val_SCXIModule) {
                triggerName = "/" + device + "/" + terminalName;
                break;
            }
        }
        return triggerName;
    }
}
