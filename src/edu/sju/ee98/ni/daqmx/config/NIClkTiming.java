/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.sju.ee98.ni.daqmx.config;

/**
 *
 * @author Leo
 */
public interface NIClkTiming {

    public double getRate();

    public long getSampsPerChanToAcquire();
}
