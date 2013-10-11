/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.sju.ee98.ni.daqmx.data;

import java.awt.Graphics;

/**
 *
 * @author Leo
 */
public interface NIWaveData extends java.io.Serializable {


    public Object getData();

    public double getRate();
}
