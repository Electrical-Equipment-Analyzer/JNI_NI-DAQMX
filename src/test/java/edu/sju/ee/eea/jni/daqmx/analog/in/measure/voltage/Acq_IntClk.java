/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.sju.ee.eea.jni.daqmx.analog.in.measure.voltage;

import edu.sju.ee.eea.jni.daqmx.DAQmx;
import java.util.logging.Level;
import java.util.logging.Logger;
import junit.framework.TestCase;

/**
 *
 * @author Leo
 */
public class Acq_IntClk extends TestCase {

    public Acq_IntClk(String testName) {
        super(testName);
    }

    @Override
    protected void setUp() throws Exception {
        super.setUp();
    }

    @Override
    protected void tearDown() throws Exception {
        super.tearDown();
    }

    // TODO add test methods here. The name must begin with 'test'. For example:
    public void test() {

        DAQmx handle = new DAQmx();
        try {
            //******************************************************************
            // DAQmx Configure Code
            handle.createTask("");
            handle.createAIVoltageChan("Dev1/ai0", "", DAQmx.Val_Cfg_Default, -10.0, 10.0, DAQmx.Val_Volts, null);
            handle.cfgSampClkTiming("", 10000.0, DAQmx.Val_Rising, DAQmx.Val_FiniteSamps, 1000);

            //******************************************************************
            // DAQmx Start Code
            handle.startTask();

            //******************************************************************
            // DAQmx Read Code
            double data[] = new double[1000];
            handle.readAnalogF64(1000, 10, DAQmx.Val_GroupByChannel, data, 1000, null);

            for (int i = 0; i < data.length; i++) {
                System.out.print(data[i] + "\t");
            }
            System.out.println();

        } catch (Exception ex) {
            Logger.getLogger(Acq_IntClk.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            try {
                if (handle.isAlive()) {
                    handle.stopTask();
                    handle.clearTask();
                }
            } catch (Exception ex) {
                Logger.getLogger(Acq_IntClk.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        handle = null;
        System.gc();
    }

}
