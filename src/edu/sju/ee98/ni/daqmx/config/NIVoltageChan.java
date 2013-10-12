/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.sju.ee98.ni.daqmx.config;

/**
 *
 * @author Leo
 */
public interface NIVoltageChan {

    public String getPhysicalChannel();

    public double getMinVoltage();

    public double getMaxVoltage();
    
}
