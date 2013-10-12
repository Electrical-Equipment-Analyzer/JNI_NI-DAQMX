/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.sju.ee98.ni.daqmx.simulator;

import edu.sju.ee98.ni.daqmx.data.NIWaveData;

/**
 *
 * @author Leo
 */
public class NIAnalogSimulator implements NIWaveData {

    
    private double[] data;
    
    public void gen() {
//        data = new double[(int) config.getLength()];
//        for (int x = 0; x < data.length; x++) {
//            data[x] = Math.sin(x / config.getRate() * 2 * Math.PI * config.getMinVoltage()) * config.getMaxVoltage();
//        }
    }
    
    @Override
    public Object getData() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public double getRate() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
}
