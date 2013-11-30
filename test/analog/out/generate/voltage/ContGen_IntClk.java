/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package analog.out.generate.voltage;

import edu.sju.ee.ni.daqmx.DAQmx;
import edu.sju.ee.ni.math.WaveGenerator;
import java.util.logging.Level;
import java.util.logging.Logger;
import synchronization.multiFunction.SynchAIAO;

/**
 *
 * @author Leo
 */
public class ContGen_IntClk {

    public static void main(String[] args) {

        double frequency = 100;
        double rate = frequency * 100;
        int length = 1000;
        WaveGenerator wg = new WaveGenerator(rate, length, 2, frequency, 0);

        DAQmx handle = new DAQmx();
        try {
            //******************************************************************
            // DAQmx Configure Code
            handle.createTask("");
            handle.createAOVoltageChan("Dev1/ao0", "", -10.0, 10.0, DAQmx.Val_Volts, null);
            handle.cfgSampClkTiming("", rate, DAQmx.Val_Rising, DAQmx.Val_ContSamps, length);

            handle.writeAnalogF64(length, false, 10.0, DAQmx.Val_GroupByChannel, wg.getData());

            //******************************************************************
            // DAQmx Start Code
            handle.startTask();

            Thread.sleep(10000);
        } catch (Exception ex) {
            Logger.getLogger(SynchAIAO.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            try {
                if (handle.isAlive()) {
                    handle.stopTask();
                    handle.clearTask();
                }
            } catch (Exception ex) {
                Logger.getLogger(SynchAIAO.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        handle = null;
        System.gc();
    }

}
