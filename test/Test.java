
import analogIn.measureVoltage.Acq_IntClk;
import edu.sju.ee.ni.daqmx.DAQmx;
import java.util.logging.Level;
import java.util.logging.Logger;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Leo
 */
public class Test {

    public static void main(String[] args) {
        DAQmx input = new DAQmx();
        DAQmx output = new DAQmx();
        try {
            //******************************************************************
            // DAQmx Configure Code
            input.createTask("");
            input.createAIVoltageChan("Dev1/ai0", "", DAQmx.Val_Cfg_Default, -10.0, 10.0, DAQmx.Val_Volts, null);
            input.cfgSampClkTiming("", 10000.0, DAQmx.Val_Rising, DAQmx.Val_FiniteSamps, 1000);
            
            output.createTask("");
            output.createAIVoltageChan("Dev1/ai1", "", DAQmx.Val_Cfg_Default, -10.0, 10.0, DAQmx.Val_Volts, null);
            output.cfgSampClkTiming("", 10000.0, DAQmx.Val_Rising, DAQmx.Val_FiniteSamps, 1000);

            //******************************************************************
            // DAQmx Start Code
            input.startTask();
            output.startTask();

            //******************************************************************
            // DAQmx Read Code
            double inputData[] = new double[1000];
            input.readAnalogF64(1000, 10, DAQmx.Val_GroupByChannel, inputData, 1000, null);

            for (int i = 0; i < inputData.length; i++) {
                System.out.print(inputData[i] + "\t");
            }
            System.out.println();
            
            
            double outputData[] = new double[1000];
            output.readAnalogF64(1000, 10, DAQmx.Val_GroupByChannel, outputData, 1000, null);

            for (int i = 0; i < outputData.length; i++) {
                System.out.print(outputData[i] + "\t");
            }
            System.out.println();

        } catch (Exception ex) {
            Logger.getLogger(Acq_IntClk.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            try {
                if (input.isAlive()) {
                    input.stopTask();
                    input.clearTask();
                }
            } catch (Exception ex) {
                Logger.getLogger(Acq_IntClk.class.getName()).log(Level.SEVERE, null, ex);
            }
            try {
                if (output.isAlive()) {
                    output.stopTask();
                    output.clearTask();
                }
            } catch (Exception ex) {
                Logger.getLogger(Acq_IntClk.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
//        daQmx.test();
        input = null;
        System.gc();
    }
}
