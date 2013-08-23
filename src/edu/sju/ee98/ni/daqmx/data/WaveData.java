/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.sju.ee98.ni.daqmx.data;

/**
 *
 * @author Leo
 */
public interface WaveData extends java.io.Serializable {

    public Object getData();
    
    public double[] getDoubleArray();
}
