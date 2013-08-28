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
public interface Grid {

    public void paintWave(Graphics g, double rate, double[] data);
}
